# Microsoft Developer Studio Project File - Name="crypto" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=crypto - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "crypto.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "crypto.mak" CFG="crypto - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "crypto - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "crypto - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "crypto - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\bin\release"
# PROP BASE Intermediate_Dir "..\..\obj\release\crypto"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin\release"
# PROP Intermediate_Dir "..\..\obj\release\crypto"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /Ob2 /I "." /I "..\..\include" /I "..\portable" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D CONFIG_CRYPTO_LHASH=1 /D CONFIG_CRYPTO_ERR=1 /D CONFIG_CRYPTO_BIO=1 /D CONFIG_CRYPTO_RSA=1 /D CONFIG_CRYPTO_DSA=1 /D CONFIG_CRYPTO_DH=1 /D CONFIG_CRYPTO_BN=1 /D CONFIG_CRYPTO_HMAC=1 /D CONFIG_CRYPTO_MD5=1 /D CONFIG_CRYPTO_SHA=1 /D CONFIG_CRYPTO_SHA1=1 /D CONFIG_CRYPTO_DES=1 /D CONFIG_CRYPTO_AES=1 /D CONFIG_CRYPTO=1 /D CONFIG_CRYPTO_IDEA=1 /D CONFIG_CRYPTO_RC4=1 /D CONFIG_SSL=1 /D CONFIG_SSL2=1 /D CONFIG_SSL3=1 /D CONFIG_TLS=1 /D CONFIG_BIO_SSL=1 /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "crypto - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\bin\debug"
# PROP BASE Intermediate_Dir "..\..\obj\debug\crypto"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin\debug"
# PROP Intermediate_Dir "..\..\obj\debug\crypto"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\portable" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D CONFIG_CRYPTO_LHASH=1 /D CONFIG_CRYPTO_ERR=1 /D CONFIG_CRYPTO_BIO=1 /D CONFIG_CRYPTO_RSA=1 /D CONFIG_CRYPTO_DSA=1 /D CONFIG_CRYPTO_DH=1 /D CONFIG_CRYPTO_BN=1 /D CONFIG_CRYPTO_HMAC=1 /D CONFIG_CRYPTO_MD5=1 /D CONFIG_CRYPTO_SHA=1 /D CONFIG_CRYPTO_SHA1=1 /D CONFIG_CRYPTO_DES=1 /D CONFIG_CRYPTO_AES=1 /D CONFIG_CRYPTO=1 /D CONFIG_CRYPTO_IDEA=1 /D CONFIG_CRYPTO_RC4=1 /D CONFIG_SSL=1 /D CONFIG_SSL2=1 /D CONFIG_SSL3=1 /D CONFIG_TLS=1 /D CONFIG_BIO_SSL=1 /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "crypto - Win32 Release"
# Name "crypto - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\a_bitstr.c
# End Source File
# Begin Source File

SOURCE=.\a_bool.c
# End Source File
# Begin Source File

SOURCE=.\a_bytes.c
# End Source File
# Begin Source File

SOURCE=.\a_d2i_fp.c
# End Source File
# Begin Source File

SOURCE=.\a_digest.c
# End Source File
# Begin Source File

SOURCE=.\a_dup.c
# End Source File
# Begin Source File

SOURCE=.\a_enum.c
# End Source File
# Begin Source File

SOURCE=.\a_gentm.c
# End Source File
# Begin Source File

SOURCE=.\a_hdr.c
# End Source File
# Begin Source File

SOURCE=.\a_i2d_fp.c
# End Source File
# Begin Source File

SOURCE=.\a_int.c
# End Source File
# Begin Source File

SOURCE=.\a_mbstr.c
# End Source File
# Begin Source File

SOURCE=.\a_meth.c
# End Source File
# Begin Source File

SOURCE=.\a_object.c
# End Source File
# Begin Source File

SOURCE=.\a_octet.c
# End Source File
# Begin Source File

SOURCE=.\a_print.c
# End Source File
# Begin Source File

SOURCE=.\a_set.c
# End Source File
# Begin Source File

SOURCE=.\a_sign.c
# End Source File
# Begin Source File

SOURCE=.\a_strex.c
# End Source File
# Begin Source File

SOURCE=.\a_strnid.c
# End Source File
# Begin Source File

SOURCE=.\a_time.c
# End Source File
# Begin Source File

SOURCE=.\a_type.c
# End Source File
# Begin Source File

SOURCE=.\a_utctm.c
# End Source File
# Begin Source File

SOURCE=.\a_utf8.c
# End Source File
# Begin Source File

SOURCE=.\a_verify.c
# End Source File
# Begin Source File

SOURCE=.\aes_cbc.c
# End Source File
# Begin Source File

SOURCE=.\aes_cfb.c
# End Source File
# Begin Source File

SOURCE=.\aes_core.c
# End Source File
# Begin Source File

SOURCE=.\aes_ctr.c
# End Source File
# Begin Source File

SOURCE=.\aes_ecb.c
# End Source File
# Begin Source File

SOURCE=.\aes_misc.c
# End Source File
# Begin Source File

SOURCE=.\aes_ofb.c
# End Source File
# Begin Source File

SOURCE=.\asn1_err.c
# End Source File
# Begin Source File

SOURCE=.\asn1_gen.c
# End Source File
# Begin Source File

SOURCE=.\asn1_lib.c
# End Source File
# Begin Source File

SOURCE=.\asn1_par.c
# End Source File
# Begin Source File

SOURCE=.\asn_pack.c
# End Source File
# Begin Source File

SOURCE=.\b_dump.c
# End Source File
# Begin Source File

SOURCE=.\b_print.c
# End Source File
# Begin Source File

SOURCE=.\b_sock.c
# End Source File
# Begin Source File

SOURCE=.\bf_buff.c
# End Source File
# Begin Source File

SOURCE=.\bf_cfb64.c
# End Source File
# Begin Source File

SOURCE=.\bf_ecb.c
# End Source File
# Begin Source File

SOURCE=.\bf_enc.c
# End Source File
# Begin Source File

SOURCE=.\bf_null.c
# End Source File
# Begin Source File

SOURCE=.\bf_ofb64.c
# End Source File
# Begin Source File

SOURCE=.\bf_skey.c
# End Source File
# Begin Source File

SOURCE=.\bio_b64.c
# End Source File
# Begin Source File

SOURCE=.\bio_enc.c
# End Source File
# Begin Source File

SOURCE=.\bio_err.c
# End Source File
# Begin Source File

SOURCE=.\bio_lib.c
# End Source File
# Begin Source File

SOURCE=.\bio_md.c
# End Source File
# Begin Source File

SOURCE=.\bio_ok.c
# End Source File
# Begin Source File

SOURCE=.\bn_add.c
# End Source File
# Begin Source File

SOURCE=.\bn_asm.c
# End Source File
# Begin Source File

SOURCE=.\bn_blind.c
# End Source File
# Begin Source File

SOURCE=.\bn_const.c
# End Source File
# Begin Source File

SOURCE=.\bn_ctx.c
# End Source File
# Begin Source File

SOURCE=.\bn_div.c
# End Source File
# Begin Source File

SOURCE=.\bn_err.c
# End Source File
# Begin Source File

SOURCE=.\bn_exp.c
# End Source File
# Begin Source File

SOURCE=.\bn_exp2.c
# End Source File
# Begin Source File

SOURCE=.\bn_gcd.c
# End Source File
# Begin Source File

SOURCE=.\bn_gf2m.c
# End Source File
# Begin Source File

SOURCE=.\bn_kron.c
# End Source File
# Begin Source File

SOURCE=.\bn_lib.c
# End Source File
# Begin Source File

SOURCE=.\bn_mod.c
# End Source File
# Begin Source File

SOURCE=.\bn_mont.c
# End Source File
# Begin Source File

SOURCE=.\bn_mpi.c
# End Source File
# Begin Source File

SOURCE=.\bn_mul.c
# End Source File
# Begin Source File

SOURCE=.\bn_nist.c
# End Source File
# Begin Source File

SOURCE=.\bn_prime.c
# End Source File
# Begin Source File

SOURCE=.\bn_print.c
# End Source File
# Begin Source File

SOURCE=.\bn_rand.c
# End Source File
# Begin Source File

SOURCE=.\bn_recp.c
# End Source File
# Begin Source File

SOURCE=.\bn_shift.c
# End Source File
# Begin Source File

SOURCE=.\bn_sqr.c
# End Source File
# Begin Source File

SOURCE=.\bn_sqrt.c
# End Source File
# Begin Source File

SOURCE=.\bn_word.c
# End Source File
# Begin Source File

SOURCE=.\bss_conn.c
# End Source File
# Begin Source File

SOURCE=.\bss_file.c
# End Source File
# Begin Source File

SOURCE=.\bss_mem.c
# End Source File
# Begin Source File

SOURCE=.\bss_null.c
# End Source File
# Begin Source File

SOURCE=.\bss_sock.c
# End Source File
# Begin Source File

SOURCE=.\buf_err.c
# End Source File
# Begin Source File

SOURCE=.\buffer.c
# End Source File
# Begin Source File

SOURCE=.\by_dir.c
# End Source File
# Begin Source File

SOURCE=.\by_file.c
# End Source File
# Begin Source File

SOURCE=.\c_all.c
# End Source File
# Begin Source File

SOURCE=.\c_allc.c
# End Source File
# Begin Source File

SOURCE=.\c_alld.c
# End Source File
# Begin Source File

SOURCE=.\c_cfb64.c
# End Source File
# Begin Source File

SOURCE=.\c_ecb.c
# End Source File
# Begin Source File

SOURCE=.\c_enc.c
# End Source File
# Begin Source File

SOURCE=.\c_ofb64.c
# End Source File
# Begin Source File

SOURCE=.\c_rle.c
# End Source File
# Begin Source File

SOURCE=.\c_skey.c
# End Source File
# Begin Source File

SOURCE=.\c_zlib.c
# End Source File
# Begin Source File

SOURCE=.\cbc3_enc.c
# End Source File
# Begin Source File

SOURCE=.\cbc_cksm.c
# End Source File
# Begin Source File

SOURCE=.\cbc_enc.c
# End Source File
# Begin Source File

SOURCE=.\cfb64ede.c
# End Source File
# Begin Source File

SOURCE=.\cfb64enc.c
# End Source File
# Begin Source File

SOURCE=.\cfb_enc.c
# End Source File
# Begin Source File

SOURCE=.\comp_err.c
# End Source File
# Begin Source File

SOURCE=.\comp_lib.c
# End Source File
# Begin Source File

SOURCE=.\conf_api.c
# End Source File
# Begin Source File

SOURCE=.\conf_def.c
# End Source File
# Begin Source File

SOURCE=.\conf_err.c
# End Source File
# Begin Source File

SOURCE=.\conf_lib.c
# End Source File
# Begin Source File

SOURCE=.\conf_list.c
# End Source File
# Begin Source File

SOURCE=.\cpt_err.c
# End Source File
# Begin Source File

SOURCE=.\cryptlib.c
# End Source File
# Begin Source File

SOURCE=.\cuversion.c
# End Source File
# Begin Source File

SOURCE=.\d2i_pr.c
# End Source File
# Begin Source File

SOURCE=.\d2i_pu.c
# End Source File
# Begin Source File

SOURCE=.\des_enc.c
# End Source File
# Begin Source File

SOURCE=.\des_old.c
# End Source File
# Begin Source File

SOURCE=.\des_old2.c
# End Source File
# Begin Source File

SOURCE=.\dh_asn1.c
# End Source File
# Begin Source File

SOURCE=.\dh_check.c
# End Source File
# Begin Source File

SOURCE=.\dh_err.c
# End Source File
# Begin Source File

SOURCE=.\dh_gen.c
# End Source File
# Begin Source File

SOURCE=.\dh_key.c
# End Source File
# Begin Source File

SOURCE=.\dh_lib.c
# End Source File
# Begin Source File

SOURCE=.\dsa_asn1.c
# End Source File
# Begin Source File

SOURCE=.\dsa_err.c
# End Source File
# Begin Source File

SOURCE=.\dsa_gen.c
# End Source File
# Begin Source File

SOURCE=.\dsa_key.c
# End Source File
# Begin Source File

SOURCE=.\dsa_lib.c
# End Source File
# Begin Source File

SOURCE=.\dsa_ossl.c
# End Source File
# Begin Source File

SOURCE=.\dsa_sign.c
# End Source File
# Begin Source File

SOURCE=.\dsa_vrf.c
# End Source File
# Begin Source File

SOURCE=.\e_aes.c
# End Source File
# Begin Source File

SOURCE=.\e_bf.c
# End Source File
# Begin Source File

SOURCE=.\e_cast.c
# End Source File
# Begin Source File

SOURCE=.\e_des.c
# End Source File
# Begin Source File

SOURCE=.\e_des3.c
# End Source File
# Begin Source File

SOURCE=.\e_idea.c
# End Source File
# Begin Source File

SOURCE=.\e_null.c
# End Source File
# Begin Source File

SOURCE=.\e_rc2.c
# End Source File
# Begin Source File

SOURCE=.\e_rc4.c
# End Source File
# Begin Source File

SOURCE=.\e_rc5.c
# End Source File
# Begin Source File

SOURCE=.\e_xcbc_d.c
# End Source File
# Begin Source File

SOURCE=.\ebcdic.c
# End Source File
# Begin Source File

SOURCE=.\ecb3_enc.c
# End Source File
# Begin Source File

SOURCE=.\ecb_enc.c
# End Source File
# Begin Source File

SOURCE=.\ede_cbcm_enc.c
# End Source File
# Begin Source File

SOURCE=.\enc_read.c
# End Source File
# Begin Source File

SOURCE=.\enc_writ.c
# End Source File
# Begin Source File

SOURCE=.\encode.c
# End Source File
# Begin Source File

SOURCE=.\err.c
# End Source File
# Begin Source File

SOURCE=.\err_all.c
# End Source File
# Begin Source File

SOURCE=.\err_prn.c
# End Source File
# Begin Source File

SOURCE=.\evp_acnf.c
# End Source File
# Begin Source File

SOURCE=.\evp_asn1.c
# End Source File
# Begin Source File

SOURCE=.\evp_dgst.c
# End Source File
# Begin Source File

SOURCE=.\evp_enc.c
# End Source File
# Begin Source File

SOURCE=.\evp_err.c
# End Source File
# Begin Source File

SOURCE=.\evp_key.c
# End Source File
# Begin Source File

SOURCE=.\evp_lib.c
# End Source File
# Begin Source File

SOURCE=.\evp_pbe.c
# End Source File
# Begin Source File

SOURCE=.\evp_pkey.c
# End Source File
# Begin Source File

SOURCE=.\ex_data.c
# End Source File
# Begin Source File

SOURCE=.\f_enum.c
# End Source File
# Begin Source File

SOURCE=.\f_int.c
# End Source File
# Begin Source File

SOURCE=.\f_string.c
# End Source File
# Begin Source File

SOURCE=.\fcrypt.c
# End Source File
# Begin Source File

SOURCE=.\fcrypt_b.c
# End Source File
# Begin Source File

SOURCE=.\hmac.c
# End Source File
# Begin Source File

SOURCE=.\i2d_pr.c
# End Source File
# Begin Source File

SOURCE=.\i2d_pu.c
# End Source File
# Begin Source File

SOURCE=.\i_cbc.c
# End Source File
# Begin Source File

SOURCE=.\i_cfb64.c
# End Source File
# Begin Source File

SOURCE=.\i_ecb.c
# End Source File
# Begin Source File

SOURCE=.\i_ofb64.c
# End Source File
# Begin Source File

SOURCE=.\i_skey.c
# End Source File
# Begin Source File

SOURCE=.\lh_stats.c
# End Source File
# Begin Source File

SOURCE=.\lhash.c
# End Source File
# Begin Source File

SOURCE=.\m_dss.c
# End Source File
# Begin Source File

SOURCE=.\m_dss1.c
# End Source File
# Begin Source File

SOURCE=.\m_md4.c
# End Source File
# Begin Source File

SOURCE=.\m_md5.c
# End Source File
# Begin Source File

SOURCE=.\m_null.c
# End Source File
# Begin Source File

SOURCE=.\m_ripemd.c
# End Source File
# Begin Source File

SOURCE=.\m_sha.c
# End Source File
# Begin Source File

SOURCE=.\m_sha1.c
# End Source File
# Begin Source File

SOURCE=.\md4_dgst.c
# End Source File
# Begin Source File

SOURCE=.\md4_one.c
# End Source File
# Begin Source File

SOURCE=.\md5_dgst.c
# End Source File
# Begin Source File

SOURCE=.\md5_one.c
# End Source File
# Begin Source File

SOURCE=.\md_rand.c
# End Source File
# Begin Source File

SOURCE=.\mem.c
# End Source File
# Begin Source File

SOURCE=.\mem_clr.c
# End Source File
# Begin Source File

SOURCE=.\mem_dbg.c
# End Source File
# Begin Source File

SOURCE=.\n_pkey.c
# End Source File
# Begin Source File

SOURCE=.\names.c
# End Source File
# Begin Source File

SOURCE=.\nsseq.c
# End Source File
# Begin Source File

SOURCE=.\o_dir.c
# End Source File
# Begin Source File

SOURCE=.\o_time.c
# End Source File
# Begin Source File

SOURCE=.\o_uid.c
# End Source File
# Begin Source File

SOURCE=.\obj_dat.c
# End Source File
# Begin Source File

SOURCE=.\obj_err.c
# End Source File
# Begin Source File

SOURCE=.\obj_lib.c
# End Source File
# Begin Source File

SOURCE=.\obj_names.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_asn.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_cl.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_err.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_ext.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_ht.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_lib.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_prn.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_srv.c
# End Source File
# Begin Source File

SOURCE=.\ocsp_vfy.c
# End Source File
# Begin Source File

SOURCE=.\ofb64ede.c
# End Source File
# Begin Source File

SOURCE=.\ofb64enc.c
# End Source File
# Begin Source File

SOURCE=.\ofb_enc.c
# End Source File
# Begin Source File

SOURCE=.\p12_add.c
# End Source File
# Begin Source File

SOURCE=.\p12_asn.c
# End Source File
# Begin Source File

SOURCE=.\p12_attr.c
# End Source File
# Begin Source File

SOURCE=.\p12_crpt.c
# End Source File
# Begin Source File

SOURCE=.\p12_crt.c
# End Source File
# Begin Source File

SOURCE=.\p12_decr.c
# End Source File
# Begin Source File

SOURCE=.\p12_init.c
# End Source File
# Begin Source File

SOURCE=.\p12_key.c
# End Source File
# Begin Source File

SOURCE=.\p12_kiss.c
# End Source File
# Begin Source File

SOURCE=.\p12_mutl.c
# End Source File
# Begin Source File

SOURCE=.\p12_npas.c
# End Source File
# Begin Source File

SOURCE=.\p12_p8d.c
# End Source File
# Begin Source File

SOURCE=.\p12_p8e.c
# End Source File
# Begin Source File

SOURCE=.\p12_utl.c
# End Source File
# Begin Source File

SOURCE=.\p5_crpt.c
# End Source File
# Begin Source File

SOURCE=.\p5_crpt2.c
# End Source File
# Begin Source File

SOURCE=.\p5_pbe.c
# End Source File
# Begin Source File

SOURCE=.\p5_pbev2.c
# End Source File
# Begin Source File

SOURCE=.\p8_pkey.c
# End Source File
# Begin Source File

SOURCE=.\p_dec.c
# End Source File
# Begin Source File

SOURCE=.\p_enc.c
# End Source File
# Begin Source File

SOURCE=.\p_lib.c
# End Source File
# Begin Source File

SOURCE=.\p_open.c
# End Source File
# Begin Source File

SOURCE=.\p_seal.c
# End Source File
# Begin Source File

SOURCE=.\p_sign.c
# End Source File
# Begin Source File

SOURCE=.\p_verify.c
# End Source File
# Begin Source File

SOURCE=.\pcbc_enc.c
# End Source File
# Begin Source File

SOURCE=.\pcy_cache.c
# End Source File
# Begin Source File

SOURCE=.\pcy_data.c
# End Source File
# Begin Source File

SOURCE=.\pcy_lib.c
# End Source File
# Begin Source File

SOURCE=.\pcy_map.c
# End Source File
# Begin Source File

SOURCE=.\pcy_node.c
# End Source File
# Begin Source File

SOURCE=.\pcy_tree.c
# End Source File
# Begin Source File

SOURCE=.\pem_all.c
# End Source File
# Begin Source File

SOURCE=.\pem_err.c
# End Source File
# Begin Source File

SOURCE=.\pem_info.c
# End Source File
# Begin Source File

SOURCE=.\pem_lib.c
# End Source File
# Begin Source File

SOURCE=.\pem_oth.c
# End Source File
# Begin Source File

SOURCE=.\pem_pk8.c
# End Source File
# Begin Source File

SOURCE=.\pem_pkey.c
# End Source File
# Begin Source File

SOURCE=.\pem_seal.c
# End Source File
# Begin Source File

SOURCE=.\pem_sign.c
# End Source File
# Begin Source File

SOURCE=.\pem_x509.c
# End Source File
# Begin Source File

SOURCE=.\pem_xaux.c
# End Source File
# Begin Source File

SOURCE=.\pk12err.c
# End Source File
# Begin Source File

SOURCE=.\pk7_asn1.c
# End Source File
# Begin Source File

SOURCE=.\pk7_attr.c
# End Source File
# Begin Source File

SOURCE=.\pk7_doit.c
# End Source File
# Begin Source File

SOURCE=.\pk7_lib.c
# End Source File
# Begin Source File

SOURCE=.\pk7_mime.c
# End Source File
# Begin Source File

SOURCE=.\pk7_smime.c
# End Source File
# Begin Source File

SOURCE=.\pkcs7err.c
# End Source File
# Begin Source File

SOURCE=.\pqueue.c
# End Source File
# Begin Source File

SOURCE=.\qud_cksm.c
# End Source File
# Begin Source File

SOURCE=.\rand_egd.c
# End Source File
# Begin Source File

SOURCE=.\rand_err.c
# End Source File
# Begin Source File

SOURCE=.\rand_key.c
# End Source File
# Begin Source File

SOURCE=.\rand_lib.c
# End Source File
# Begin Source File

SOURCE=.\rand_unix.c
# End Source File
# Begin Source File

SOURCE=.\rand_win.c
# End Source File
# Begin Source File

SOURCE=.\randfile.c
# End Source File
# Begin Source File

SOURCE=.\rc2_cbc.c
# End Source File
# Begin Source File

SOURCE=.\rc2_ecb.c
# End Source File
# Begin Source File

SOURCE=.\rc2_skey.c
# End Source File
# Begin Source File

SOURCE=.\rc2cfb64.c
# End Source File
# Begin Source File

SOURCE=.\rc2ofb64.c
# End Source File
# Begin Source File

SOURCE=.\rc4_enc.c
# End Source File
# Begin Source File

SOURCE=.\rc4_skey.c
# End Source File
# Begin Source File

SOURCE=.\rc5_ecb.c
# End Source File
# Begin Source File

SOURCE=.\rc5_enc.c
# End Source File
# Begin Source File

SOURCE=.\rc5_skey.c
# End Source File
# Begin Source File

SOURCE=.\rc5cfb64.c
# End Source File
# Begin Source File

SOURCE=.\rc5ofb64.c
# End Source File
# Begin Source File

SOURCE=.\read2pwd.c
# End Source File
# Begin Source File

SOURCE=.\rmd_dgst.c
# End Source File
# Begin Source File

SOURCE=.\rmd_one.c
# End Source File
# Begin Source File

SOURCE=.\rpc_enc.c
# End Source File
# Begin Source File

SOURCE=.\rsa_asn1.c
# End Source File
# Begin Source File

SOURCE=.\rsa_chk.c
# End Source File
# Begin Source File

SOURCE=.\rsa_eay.c
# End Source File
# Begin Source File

SOURCE=.\rsa_err.c
# End Source File
# Begin Source File

SOURCE=.\rsa_gen.c
# End Source File
# Begin Source File

SOURCE=.\rsa_lib.c
# End Source File
# Begin Source File

SOURCE=.\rsa_none.c
# End Source File
# Begin Source File

SOURCE=.\rsa_null.c
# End Source File
# Begin Source File

SOURCE=.\rsa_oaep.c
# End Source File
# Begin Source File

SOURCE=.\rsa_pk1.c
# End Source File
# Begin Source File

SOURCE=.\rsa_pss.c
# End Source File
# Begin Source File

SOURCE=.\rsa_saos.c
# End Source File
# Begin Source File

SOURCE=.\rsa_sign.c
# End Source File
# Begin Source File

SOURCE=.\rsa_ssl.c
# End Source File
# Begin Source File

SOURCE=.\rsa_x931.c
# End Source File
# Begin Source File

SOURCE=.\set_key.c
# End Source File
# Begin Source File

SOURCE=.\sha1_one.c
# End Source File
# Begin Source File

SOURCE=.\sha1dgst.c
# End Source File
# Begin Source File

SOURCE=.\sha256.c
# End Source File
# Begin Source File

SOURCE=.\sha512.c
# End Source File
# Begin Source File

SOURCE=.\sha_dgst.c
# End Source File
# Begin Source File

SOURCE=.\sha_one.c
# End Source File
# Begin Source File

SOURCE=.\stack.c
# End Source File
# Begin Source File

SOURCE=.\str2key.c
# End Source File
# Begin Source File

SOURCE=.\t_bitst.c
# End Source File
# Begin Source File

SOURCE=.\t_crl.c
# End Source File
# Begin Source File

SOURCE=.\t_pkey.c
# End Source File
# Begin Source File

SOURCE=.\t_req.c
# End Source File
# Begin Source File

SOURCE=.\t_spki.c
# End Source File
# Begin Source File

SOURCE=.\t_x509.c
# End Source File
# Begin Source File

SOURCE=.\t_x509a.c
# End Source File
# Begin Source File

SOURCE=.\tasn_dec.c
# End Source File
# Begin Source File

SOURCE=.\tasn_enc.c
# End Source File
# Begin Source File

SOURCE=.\tasn_fre.c
# End Source File
# Begin Source File

SOURCE=.\tasn_new.c
# End Source File
# Begin Source File

SOURCE=.\tasn_typ.c
# End Source File
# Begin Source File

SOURCE=.\tasn_utl.c
# End Source File
# Begin Source File

SOURCE=.\ui_compat.c
# End Source File
# Begin Source File

SOURCE=.\ui_err.c
# End Source File
# Begin Source File

SOURCE=.\ui_lib.c
# End Source File
# Begin Source File

SOURCE=.\ui_openssl.c
# End Source File
# Begin Source File

SOURCE=.\ui_util.c
# End Source File
# Begin Source File

SOURCE=.\uplink.c
# End Source File
# Begin Source File

SOURCE=.\v3_akey.c
# End Source File
# Begin Source File

SOURCE=.\v3_akeya.c
# End Source File
# Begin Source File

SOURCE=.\v3_alt.c
# End Source File
# Begin Source File

SOURCE=.\v3_bcons.c
# End Source File
# Begin Source File

SOURCE=.\v3_bitst.c
# End Source File
# Begin Source File

SOURCE=.\v3_conf.c
# End Source File
# Begin Source File

SOURCE=.\v3_cpols.c
# End Source File
# Begin Source File

SOURCE=.\v3_crld.c
# End Source File
# Begin Source File

SOURCE=.\v3_enum.c
# End Source File
# Begin Source File

SOURCE=.\v3_extku.c
# End Source File
# Begin Source File

SOURCE=.\v3_genn.c
# End Source File
# Begin Source File

SOURCE=.\v3_ia5.c
# End Source File
# Begin Source File

SOURCE=.\v3_info.c
# End Source File
# Begin Source File

SOURCE=.\v3_int.c
# End Source File
# Begin Source File

SOURCE=.\v3_lib.c
# End Source File
# Begin Source File

SOURCE=.\v3_ncons.c
# End Source File
# Begin Source File

SOURCE=.\v3_ocsp.c
# End Source File
# Begin Source File

SOURCE=.\v3_pci.c
# End Source File
# Begin Source File

SOURCE=.\v3_pcia.c
# End Source File
# Begin Source File

SOURCE=.\v3_pcons.c
# End Source File
# Begin Source File

SOURCE=.\v3_pku.c
# End Source File
# Begin Source File

SOURCE=.\v3_pmaps.c
# End Source File
# Begin Source File

SOURCE=.\v3_prn.c
# End Source File
# Begin Source File

SOURCE=.\v3_purp.c
# End Source File
# Begin Source File

SOURCE=.\v3_skey.c
# End Source File
# Begin Source File

SOURCE=.\v3_sxnet.c
# End Source File
# Begin Source File

SOURCE=.\v3_utl.c
# End Source File
# Begin Source File

SOURCE=.\v3err.c
# End Source File
# Begin Source File

SOURCE=.\x509_att.c
# End Source File
# Begin Source File

SOURCE=.\x509_cmp.c
# End Source File
# Begin Source File

SOURCE=.\x509_d2.c
# End Source File
# Begin Source File

SOURCE=.\x509_def.c
# End Source File
# Begin Source File

SOURCE=.\x509_err.c
# End Source File
# Begin Source File

SOURCE=.\x509_ext.c
# End Source File
# Begin Source File

SOURCE=.\x509_lu.c
# End Source File
# Begin Source File

SOURCE=.\x509_obj.c
# End Source File
# Begin Source File

SOURCE=.\x509_r2x.c
# End Source File
# Begin Source File

SOURCE=.\x509_req.c
# End Source File
# Begin Source File

SOURCE=.\x509_set.c
# End Source File
# Begin Source File

SOURCE=.\x509_trs.c
# End Source File
# Begin Source File

SOURCE=.\x509_txt.c
# End Source File
# Begin Source File

SOURCE=.\x509_v3.c
# End Source File
# Begin Source File

SOURCE=.\x509_vfy.c
# End Source File
# Begin Source File

SOURCE=.\x509_vpm.c
# End Source File
# Begin Source File

SOURCE=.\x509cset.c
# End Source File
# Begin Source File

SOURCE=.\x509name.c
# End Source File
# Begin Source File

SOURCE=.\x509rset.c
# End Source File
# Begin Source File

SOURCE=.\x509spki.c
# End Source File
# Begin Source File

SOURCE=.\x509type.c
# End Source File
# Begin Source File

SOURCE=.\x_algor.c
# End Source File
# Begin Source File

SOURCE=.\x_all.c
# End Source File
# Begin Source File

SOURCE=.\x_attrib.c
# End Source File
# Begin Source File

SOURCE=.\x_bignum.c
# End Source File
# Begin Source File

SOURCE=.\x_crl.c
# End Source File
# Begin Source File

SOURCE=.\x_exten.c
# End Source File
# Begin Source File

SOURCE=.\x_info.c
# End Source File
# Begin Source File

SOURCE=.\x_long.c
# End Source File
# Begin Source File

SOURCE=.\x_name.c
# End Source File
# Begin Source File

SOURCE=.\x_pkey.c
# End Source File
# Begin Source File

SOURCE=.\x_pubkey.c
# End Source File
# Begin Source File

SOURCE=.\x_req.c
# End Source File
# Begin Source File

SOURCE=.\x_sig.c
# End Source File
# Begin Source File

SOURCE=.\x_spki.c
# End Source File
# Begin Source File

SOURCE=.\x_val.c
# End Source File
# Begin Source File

SOURCE=.\x_x509.c
# End Source File
# Begin Source File

SOURCE=.\x_x509a.c
# End Source File
# Begin Source File

SOURCE=.\xcbc_enc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\aes_locl.h
# End Source File
# Begin Source File

SOURCE=.\bf_locl.h
# End Source File
# Begin Source File

SOURCE=.\bf_pi.h
# End Source File
# Begin Source File

SOURCE=.\bio_lcl.h
# End Source File
# Begin Source File

SOURCE=.\bn_lcl.h
# End Source File
# Begin Source File

SOURCE=.\bn_prime.h
# End Source File
# Begin Source File

SOURCE=.\cast_lcl.h
# End Source File
# Begin Source File

SOURCE=.\cast_s.h
# End Source File
# Begin Source File

SOURCE=.\charmap.h
# End Source File
# Begin Source File

SOURCE=.\conf_def.h
# End Source File
# Begin Source File

SOURCE=.\cryptlib.h
# End Source File
# Begin Source File

SOURCE=.\des_locl.h
# End Source File
# Begin Source File

SOURCE=.\des_ver.h
# End Source File
# Begin Source File

SOURCE=.\e_os.h
# End Source File
# Begin Source File

SOURCE=.\evp_locl.h
# End Source File
# Begin Source File

SOURCE=.\ext_dat.h
# End Source File
# Begin Source File

SOURCE=.\idea_lcl.h
# End Source File
# Begin Source File

SOURCE=.\md32_common.h
# End Source File
# Begin Source File

SOURCE=.\md4_locl.h
# End Source File
# Begin Source File

SOURCE=.\md5_locl.h
# End Source File
# Begin Source File

SOURCE=.\o_dir.h
# End Source File
# Begin Source File

SOURCE=.\o_time.h
# End Source File
# Begin Source File

SOURCE=.\obj_dat.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl.h
# End Source File
# Begin Source File

SOURCE=.\pcy_int.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\pem.h
# End Source File
# Begin Source File

SOURCE=.\pqueue.h
# End Source File
# Begin Source File

SOURCE=.\rand_lcl.h
# End Source File
# Begin Source File

SOURCE=.\rc2_locl.h
# End Source File
# Begin Source File

SOURCE=.\rc4_locl.h
# End Source File
# Begin Source File

SOURCE=.\rc5_locl.h
# End Source File
# Begin Source File

SOURCE=.\rmd_locl.h
# End Source File
# Begin Source File

SOURCE=.\rmdconst.h
# End Source File
# Begin Source File

SOURCE=.\rpc_des.h
# End Source File
# Begin Source File

SOURCE=.\sha_locl.h
# End Source File
# Begin Source File

SOURCE=.\spr.h
# End Source File
# Begin Source File

SOURCE=.\ui_locl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Kbuild
# End Source File
# Begin Source File

SOURCE=.\Kconfig
# End Source File
# End Target
# End Project
