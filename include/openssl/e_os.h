/* e_os.h */
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

#ifndef HEADER_E_OS_H
#define HEADER_E_OS_H

#include <openssl/opensslconf.h>

#include <openssl/e_os2.h>
/* <openssl/e_os2.h> contains what we can justify to make visible
 * to the outside; this file e_os.h is not part of the exported
 * interface. */

#ifdef  __cplusplus
extern "C" {
#endif

/* Used to checking reference counts, most while doing perl5 stuff :-) */
#ifdef REF_PRINT
#undef REF_PRINT
#define REF_PRINT(a,b)	fprintf(stderr,"%08X:%4d:%s\n",(int)b,b->references,a)
#endif

#ifndef DEVRANDOM
/* set this to a comma-separated list of 'random' device files to try out.
 * My default, we will try to read at least one of these files */
#define DEVRANDOM "/dev/urandom","/dev/random","/dev/srandom"
#endif
#ifndef DEVRANDOM_EGD
/* set this to a comma-seperated list of 'egd' sockets to try out. These
 * sockets will be tried in the order listed in case accessing the device files
 * listed in DEVRANDOM did not return enough entropy. */
#define DEVRANDOM_EGD "/var/run/egd-pool","/dev/egd-pool","/etc/egd-pool","/etc/entropy"
#endif

/********************************************************************
 The Microsoft section
 ********************************************************************/
/* The following is used becaue of the small stack in some
 * Microsoft operating systems */
#ifdef WIN32
#  define MS_STATIC	static
#else
#  define MS_STATIC
#endif

#if defined(OPENSSL_SYS_WIN32) && !defined(WIN32)
#  define WIN32
#endif
#if defined(OPENSSL_SYS_WINDOWS) && !defined(WINDOWS)
#  define WINDOWS
#endif
#if defined(OPENSSL_SYS_MSDOS) && !defined(MSDOS)
#  define MSDOS
#endif

#if defined(MSDOS) && !defined(GETPID_IS_MEANINGLESS)
#  define GETPID_IS_MEANINGLESS
#endif

#ifdef WIN32
#define get_last_sys_error()	GetLastError()
#define clear_sys_error()	SetLastError(0)
#if !defined(WINNT)
#define WIN_CONSOLE_BUG
#endif
#else
#define get_last_sys_error()	errno
#define clear_sys_error()	errno=0
#endif

#if defined(WINDOWS)
#define get_last_socket_error()	WSAGetLastError()
#define clear_socket_error()	WSASetLastError(0)
#define readsocket(s,b,n)	recv((s),(b),(n),0)
#define writesocket(s,b,n)	send((s),(b),(n),0)
#define EADDRINUSE		WSAEADDRINUSE
#else
#define get_last_socket_error()	errno
#define clear_socket_error()	errno=0
#define ioctlsocket(a,b,c)	ioctl(a,b,c)
#define closesocket(s)		close(s)
#define readsocket(s,b,n)	read((s),(b),(n))
#define writesocket(s,b,n)	write((s),(b),(n))
#endif

#  define MS_CALLBACK
#  define MS_FAR

#if defined(WINDOWS)
#  ifndef S_IFDIR
#    define S_IFDIR	_S_IFDIR
#  endif
#  ifndef S_IFMT
#    define S_IFMT	_S_IFMT
#  endif

#  define NO_DIRENT

#  ifdef WINDOWS
#    if !defined(_WIN32_WCE) && !defined(_WIN32_WINNT)
       /*
	* Defining _WIN32_WINNT here in e_os.h implies certain "discipline."
	* Most notably we ought to check for availability of each specific
	* routine with GetProcAddress() and/or quard NT-specific calls with
	* GetVersion() < 0x80000000. One can argue that in latter "or" case
	* we ought to /DELAYLOAD some .DLLs in order to protect ourselves
	* against run-time link errors. This doesn't seem to be necessary,
	* because it turned out that already Windows 95, first non-NT Win32
	* implementation, is equipped with at least NT 3.51 stubs, dummy
	* routines with same name, but which do nothing. Meaning that it's
	* apparently appropriate to guard generic NT calls with GetVersion
	* alone, while NT 4.0 and above calls ought to be additionally
	* checked upon with GetProcAddress.
	*/
#      define _WIN32_WINNT 0x0400
#    endif
#    include <windows.h>
#    include <stddef.h>
#    include <errno.h>
#    include <string.h>
#    ifdef _WIN64
#      define strlen(s) _strlen31(s)
/* cut strings to 2GB */
static unsigned int _strlen31(const char *str)
	{
	unsigned int len=0;
	while (*str && len<0x80000000U) str++, len++;
	return len&0x7FFFFFFF;
	}
#    endif
#    include <malloc.h>
#  endif
#  include <io.h>
#  include <fcntl.h>

#  define ssize_t long

#  define EXIT(n) exit(n)
#  define LIST_SEPARATOR_CHAR ';'
#  ifndef X_OK
#    define X_OK	0
#  endif
#  ifndef W_OK
#    define W_OK	2
#  endif
#  ifndef R_OK
#    define R_OK	4
#  endif
#  define OPENSSL_CONF	"openssl.cnf"
#  define SSLEAY_CONF	OPENSSL_CONF
#  define NUL_DEV	"nul"
#  define RFILE		".rnd"
#  define DEFAULT_HOME  "C:"

#else /* The non-microsoft world world */

#    ifdef OPENSSL_UNISTD
#      include OPENSSL_UNISTD
#    else
#      include <unistd.h>
#    endif
#    include <sys/types.h>

#    define OPENSSL_CONF	"openssl.cnf"
#    define SSLEAY_CONF		OPENSSL_CONF
#    define RFILE		".rnd"
#    define LIST_SEPARATOR_CHAR ':'
#    define NUL_DEV		"/dev/null"
#    define EXIT(n)		exit(n)

#  define SSLeay_getpid()	getpid()

#endif


/*************/

#ifdef USE_SOCKETS
#  if defined(WINDOWS)
      /* windows world */

#    ifndef CONFIG_BIO_SOCK
#      define SSLeay_Write(a,b,c)	(-1)
#      define SSLeay_Read(a,b,c)	(-1)
#      define SHUTDOWN(fd)		close(fd)
#      define SHUTDOWN2(fd)		close(fd)
#    else
#      include <winsock.h>
extern HINSTANCE _hInstance;
#      ifdef _WIN64
/*
 * Even though sizeof(SOCKET) is 8, it's safe to cast it to int, because
 * the value constitutes an index in per-process table of limited size
 * and not a real pointer.
 */
#        define socket(d,t,p)	((int)socket(d,t,p))
#        define accept(s,f,l)	((int)accept(s,f,l))
#      endif
#      define SSLeay_Write(a,b,c)	send((a),(b),(c),0)
#      define SSLeay_Read(a,b,c)	recv((a),(b),(c),0)
#      define SHUTDOWN(fd)		{ shutdown((fd),0); closesocket(fd); }
#      define SHUTDOWN2(fd)		{ shutdown((fd),2); closesocket(fd); }
#    endif

#  else

#    include <sys/param.h>

#    include <netdb.h>
#    include <sys/socket.h>
#    ifdef FILIO_H
#      include <sys/filio.h> /* Added for FIONBIO under unixware */
#    endif
#    include <netinet/in.h>
#    include <arpa/inet.h>

#    include <sys/ioctl.h>

#    define SSLeay_Read(a,b,c)     read((a),(b),(c))
#    define SSLeay_Write(a,b,c)    write((a),(b),(c))
#    define SHUTDOWN(fd)    { shutdown((fd),0); closesocket((fd)); }
#    define SHUTDOWN2(fd)   { shutdown((fd),2); closesocket((fd)); }
#    ifndef INVALID_SOCKET
#    define INVALID_SOCKET	(-1)
#    endif /* INVALID_SOCKET */
#  endif
#endif

#ifndef OPENSSL_EXIT
# if defined(MONOLITH) && !defined(OPENSSL_C)
#  define OPENSSL_EXIT(n) return(n)
# else
#  define OPENSSL_EXIT(n) do { EXIT(n); return(n); } while(0)
# endif
#endif

/***********************************************/

/* do we need to do this for getenv.
 * Just define getenv for use under windows */

#define Getenv getenv

#define DG_GCC_BUG	/* gcc < 2.6.3 on DGUX */

#if defined(OPENSSL_SYS_WINDOWS)
#  define strcasecmp _stricmp
#  define strncasecmp _strnicmp
#else
#  ifdef NO_STRINGS_H
    int	strcasecmp();
    int	strncasecmp();
#  else
#    include <strings.h>
#  endif /* NO_STRINGS_H */
#endif

#ifdef  __cplusplus
}
#endif

#endif

