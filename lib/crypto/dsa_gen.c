/* crypto/dsa/dsa_gen.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#undef GENUINE_DSA

#ifdef GENUINE_DSA
/* Parameter generation follows the original release of FIPS PUB 186,
 * Appendix 2.2 (i.e. use SHA as defined in FIPS PUB 180) */
#define HASH    EVP_sha()
#else
/* Parameter generation follows the updated Appendix 2.2 for FIPS PUB 186,
 * also Appendix 2.2 of FIPS PUB 186-1 (i.e. use SHA as defined in
 * FIPS PUB 180-1) */
#define HASH    EVP_sha1()
#endif 

#include <openssl/opensslconf.h> /* To see if CONFIG_CRYPTO_SHA is defined */

#ifdef CONFIG_CRYPTO_SHA

#include <stdio.h>
#include <time.h>
#include "cryptlib.h"
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/dsa.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

static int dsa_builtin_paramgen(DSA *ret, int bits,
		unsigned char *seed_in, int seed_len,
		int *counter_ret, unsigned long *h_ret, BN_GENCB *cb);

int DSA_generate_parameters_ex(DSA *ret, int bits,
		unsigned char *seed_in, int seed_len,
		int *counter_ret, unsigned long *h_ret, BN_GENCB *cb)
{
	if(ret->meth->dsa_paramgen)
		return ret->meth->dsa_paramgen(ret, bits, seed_in, seed_len,
				counter_ret, h_ret, cb);
	return dsa_builtin_paramgen(ret, bits, seed_in, seed_len,
			counter_ret, h_ret, cb);
}

DSA *DSA_generate_parameters(int bits,
		unsigned char *seed_in, int seed_len,
		int *counter_ret, unsigned long *h_ret,
		void (*callback)(int, int, void *),
		void *cb_arg)
{
	BN_GENCB cb;
	DSA *ret;

	if ((ret=DSA_new()) == NULL) return NULL;

	BN_GENCB_set_old(&cb, callback, cb_arg);

	if(DSA_generate_parameters_ex(ret, bits, seed_in, seed_len,
				counter_ret, h_ret, &cb))
		return ret;
	DSA_free(ret);
	return NULL;
}

static int dsa_builtin_paramgen(DSA *ret, int bits,
		unsigned char *seed_in, int seed_len,
		int *counter_ret, unsigned long *h_ret, BN_GENCB *cb)
	{
	int ok=0;
	unsigned char seed[SHA_DIGEST_LENGTH];
	unsigned char md[SHA_DIGEST_LENGTH];
	unsigned char buf[SHA_DIGEST_LENGTH],buf2[SHA_DIGEST_LENGTH];
	BIGNUM *r0,*W,*X,*c,*test;
	BIGNUM *g=NULL,*q=NULL,*p=NULL;
	BN_MONT_CTX *mont=NULL;
	int k,n=0,i,b,m=0;
	int counter=0;
	int r=0;
	BN_CTX *ctx=NULL;
	unsigned int h=2;

	if (bits < 512) bits=512;
	bits=(bits+63)/64*64;

	if (seed_len < 20)
		seed_in = NULL; /* seed buffer too small -- ignore */
	if (seed_len > 20) 
		seed_len = 20; /* App. 2.2 of FIPS PUB 186 allows larger SEED,
		                * but our internal buffers are restricted to 160 bits*/
	if ((seed_in != NULL) && (seed_len == 20))
		memcpy(seed,seed_in,seed_len);

	if ((ctx=BN_CTX_new()) == NULL) goto err;

	if ((mont=BN_MONT_CTX_new()) == NULL) goto err;

	BN_CTX_start(ctx);
	r0 = BN_CTX_get(ctx);
	g = BN_CTX_get(ctx);
	W = BN_CTX_get(ctx);
	q = BN_CTX_get(ctx);
	X = BN_CTX_get(ctx);
	c = BN_CTX_get(ctx);
	p = BN_CTX_get(ctx);
	test = BN_CTX_get(ctx);

	if (!BN_lshift(test,BN_value_one(),bits-1))
		goto err;

	for (;;)
		{
		for (;;) /* find q */
			{
			int seed_is_random;

			/* step 1 */
			if(!BN_GENCB_call(cb, 0, m++))
				goto err;

			if (!seed_len)
				{
				RAND_pseudo_bytes(seed,SHA_DIGEST_LENGTH);
				seed_is_random = 1;
				}
			else
				{
				seed_is_random = 0;
				seed_len=0; /* use random seed if 'seed_in' turns out to be bad*/
				}
			memcpy(buf,seed,SHA_DIGEST_LENGTH);
			memcpy(buf2,seed,SHA_DIGEST_LENGTH);
			/* precompute "SEED + 1" for step 7: */
			for (i=SHA_DIGEST_LENGTH-1; i >= 0; i--)
				{
				buf[i]++;
				if (buf[i] != 0) break;
				}

			/* step 2 */
			EVP_Digest(seed,SHA_DIGEST_LENGTH,md,NULL,HASH, NULL);
			EVP_Digest(buf,SHA_DIGEST_LENGTH,buf2,NULL,HASH, NULL);
			for (i=0; i<SHA_DIGEST_LENGTH; i++)
				md[i]^=buf2[i];

			/* step 3 */
			md[0]|=0x80;
			md[SHA_DIGEST_LENGTH-1]|=0x01;
			if (!BN_bin2bn(md,SHA_DIGEST_LENGTH,q)) goto err;

			/* step 4 */
			r = BN_is_prime_fasttest_ex(q, DSS_prime_checks, ctx,
					seed_is_random, cb);
			if (r > 0)
				break;
			if (r != 0)
				goto err;

			/* do a callback call */
			/* step 5 */
			}

		if(!BN_GENCB_call(cb, 2, 0)) goto err;
		if(!BN_GENCB_call(cb, 3, 0)) goto err;

		/* step 6 */
		counter=0;
		/* "offset = 2" */

		n=(bits-1)/160;
		b=(bits-1)-n*160;

		for (;;)
			{
			if ((counter != 0) && !BN_GENCB_call(cb, 0, counter))
				goto err;

			/* step 7 */
			BN_zero(W);
			/* now 'buf' contains "SEED + offset - 1" */
			for (k=0; k<=n; k++)
				{
				/* obtain "SEED + offset + k" by incrementing: */
				for (i=SHA_DIGEST_LENGTH-1; i >= 0; i--)
					{
					buf[i]++;
					if (buf[i] != 0) break;
					}

				EVP_Digest(buf,SHA_DIGEST_LENGTH,md,NULL,HASH, NULL);

				/* step 8 */
				if (!BN_bin2bn(md,SHA_DIGEST_LENGTH,r0))
					goto err;
				if (!BN_lshift(r0,r0,160*k)) goto err;
				if (!BN_add(W,W,r0)) goto err;
				}

			/* more of step 8 */
			if (!BN_mask_bits(W,bits-1)) goto err;
			if (!BN_copy(X,W)) goto err;
			if (!BN_add(X,X,test)) goto err;

			/* step 9 */
			if (!BN_lshift1(r0,q)) goto err;
			if (!BN_mod(c,X,r0,ctx)) goto err;
			if (!BN_sub(r0,c,BN_value_one())) goto err;
			if (!BN_sub(p,X,r0)) goto err;

			/* step 10 */
			if (BN_cmp(p,test) >= 0)
				{
				/* step 11 */
				r = BN_is_prime_fasttest_ex(p, DSS_prime_checks,
						ctx, 1, cb);
				if (r > 0)
						goto end; /* found it */
				if (r != 0)
					goto err;
				}

			/* step 13 */
			counter++;
			/* "offset = offset + n + 1" */

			/* step 14 */
			if (counter >= 4096) break;
			}
		}
end:
	if(!BN_GENCB_call(cb, 2, 1))
		goto err;

	/* We now need to generate g */
	/* Set r0=(p-1)/q */
	if (!BN_sub(test,p,BN_value_one())) goto err;
	if (!BN_div(r0,NULL,test,q,ctx)) goto err;

	if (!BN_set_word(test,h)) goto err;
	if (!BN_MONT_CTX_set(mont,p,ctx)) goto err;

	for (;;)
		{
		/* g=test^r0%p */
		if (!BN_mod_exp_mont(g,test,r0,p,ctx,mont)) goto err;
		if (!BN_is_one(g)) break;
		if (!BN_add(test,test,BN_value_one())) goto err;
		h++;
		}

	if(!BN_GENCB_call(cb, 3, 1))
		goto err;

	ok=1;
err:
	if (ok)
		{
		if(ret->p) BN_free(ret->p);
		if(ret->q) BN_free(ret->q);
		if(ret->g) BN_free(ret->g);
		ret->p=BN_dup(p);
		ret->q=BN_dup(q);
		ret->g=BN_dup(g);
		if (ret->p == NULL || ret->q == NULL || ret->g == NULL)
			{
			ok=0;
			goto err;
			}
		if ((m > 1) && (seed_in != NULL)) memcpy(seed_in,seed,20);
		if (counter_ret != NULL) *counter_ret=counter;
		if (h_ret != NULL) *h_ret=h;
		}
	if(ctx)
		{
		BN_CTX_end(ctx);
		BN_CTX_free(ctx);
		}
	if (mont != NULL) BN_MONT_CTX_free(mont);
	return ok;
	}
#endif
