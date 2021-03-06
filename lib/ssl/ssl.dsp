# Microsoft Developer Studio Project File - Name="ssl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ssl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ssl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ssl.mak" CFG="ssl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ssl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ssl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ssl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\bin\release"
# PROP BASE Intermediate_Dir "..\..\obj\release\ssl"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin\release"
# PROP Intermediate_Dir "..\..\obj\release\ssl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /Ob2 /I "." /I "../../include" /I "../../lib/portable" /I "../../" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ssl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\bin\debug"
# PROP BASE Intermediate_Dir "..\..\obj\debug\ssl"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin\debug"
# PROP Intermediate_Dir "..\..\obj\debug\ssl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "../../include" /I "../../lib/portable" /I "../../" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "ssl - Win32 Release"
# Name "ssl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bio_ssl.c
# End Source File
# Begin Source File

SOURCE=.\d1_both.c
# End Source File
# Begin Source File

SOURCE=.\d1_clnt.c
# End Source File
# Begin Source File

SOURCE=.\d1_enc.c
# End Source File
# Begin Source File

SOURCE=.\d1_lib.c
# End Source File
# Begin Source File

SOURCE=.\d1_meth.c
# End Source File
# Begin Source File

SOURCE=.\d1_pkt.c
# End Source File
# Begin Source File

SOURCE=.\d1_srvr.c
# End Source File
# Begin Source File

SOURCE=.\s23_clnt.c
# End Source File
# Begin Source File

SOURCE=.\s23_lib.c
# End Source File
# Begin Source File

SOURCE=.\s23_meth.c
# End Source File
# Begin Source File

SOURCE=.\s23_pkt.c
# End Source File
# Begin Source File

SOURCE=.\s23_srvr.c
# End Source File
# Begin Source File

SOURCE=.\s2_clnt.c
# End Source File
# Begin Source File

SOURCE=.\s2_enc.c
# End Source File
# Begin Source File

SOURCE=.\s2_lib.c
# End Source File
# Begin Source File

SOURCE=.\s2_meth.c
# End Source File
# Begin Source File

SOURCE=.\s2_pkt.c
# End Source File
# Begin Source File

SOURCE=.\s2_srvr.c
# End Source File
# Begin Source File

SOURCE=.\s3_both.c
# End Source File
# Begin Source File

SOURCE=.\s3_clnt.c
# End Source File
# Begin Source File

SOURCE=.\s3_enc.c
# End Source File
# Begin Source File

SOURCE=.\s3_lib.c
# End Source File
# Begin Source File

SOURCE=.\s3_meth.c
# End Source File
# Begin Source File

SOURCE=.\s3_pkt.c
# End Source File
# Begin Source File

SOURCE=.\s3_srvr.c
# End Source File
# Begin Source File

SOURCE=.\ssl_algs.c
# End Source File
# Begin Source File

SOURCE=.\ssl_asn1.c
# End Source File
# Begin Source File

SOURCE=.\ssl_cert.c
# End Source File
# Begin Source File

SOURCE=.\ssl_ciph.c
# End Source File
# Begin Source File

SOURCE=.\ssl_err.c
# End Source File
# Begin Source File

SOURCE=.\ssl_err2.c
# End Source File
# Begin Source File

SOURCE=.\ssl_lib.c
# End Source File
# Begin Source File

SOURCE=.\ssl_rsa.c
# End Source File
# Begin Source File

SOURCE=.\ssl_sess.c
# End Source File
# Begin Source File

SOURCE=.\ssl_stat.c
# End Source File
# Begin Source File

SOURCE=.\ssl_txt.c
# End Source File
# Begin Source File

SOURCE=.\t1_clnt.c
# End Source File
# Begin Source File

SOURCE=.\t1_enc.c
# End Source File
# Begin Source File

SOURCE=.\t1_lib.c
# End Source File
# Begin Source File

SOURCE=.\t1_meth.c
# End Source File
# Begin Source File

SOURCE=.\t1_srvr.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\openssl\asn1.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\asn1_mac.h
# End Source File
# Begin Source File

SOURCE=..\portable\autoconf.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\bio.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\bn.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\comp.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\conf.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\crypto.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\dh.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\dsa.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\dtls1.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\e_os.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\e_os2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\err.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\evp.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\hmac.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\lhash.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\md5.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\o_dir.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\obj_mac.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\objects.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\opensslconf.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\opensslv.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\ossl_typ.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\pem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\pem2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\pkcs7.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\pq_compat.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\pqueue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\rand.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\rsa.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\safestack.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\sha.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\ssl.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\ssl2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\ssl23.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\ssl3.h
# End Source File
# Begin Source File

SOURCE=.\ssl_locl.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\stack.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\tls1.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\x509.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\x509_vfy.h
# End Source File
# Begin Source File

SOURCE=..\..\include\openssl\x509v3.h
# End Source File
# End Group
# End Target
# End Project
