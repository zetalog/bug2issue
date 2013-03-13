# Microsoft Developer Studio Project File - Name="curl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=curl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "curl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "curl.mak" CFG="curl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "curl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "curl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "curl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\bin\release"
# PROP BASE Intermediate_Dir "..\..\obj\release\curl"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin\release"
# PROP Intermediate_Dir "..\..\obj\release\curl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "..\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "BUILDING_LIBCURL" /D "CURL_STATICLIB" /D "ALLOW_MSVC6_WITHOUT_PSDK" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /I "..\..\lib\portable" /D "NDEBUG" /D "BUILDING_LIBCURL" /D "USE_SSLEAY" /D "USE_OPENSSL" /D "CURL_STATICLIB" /D "WIN32" /D "_MBCS" /D "CURL_DISABLE_PROXY" /FD /D "CURL_DISABLE_LIBCURL_OPTION" /D "ALLOW_MSVC6_WITHOUT_PSDK" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 kernel32.lib user32.lib advapi32.lib gdi32.lib /nologo
# ADD LIB32 kernel32.lib user32.lib advapi32.lib gdi32.lib /nologo

!ELSEIF  "$(CFG)" == "curl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\bin\debug"
# PROP BASE Intermediate_Dir "..\..\obj\debug\curl"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin\debug"
# PROP Intermediate_Dir "..\..\obj\debug\curl"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "BUILDING_LIBCURL" /D "CURL_STATICLIB" /D "ALLOW_MSVC6_WITHOUT_PSDK" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\include" /I "..\..\lib\portable" /D "BUILDING_LIBCURL" /D "USE_SSLEAY" /D "USE_OPENSSL" /D "_DEBUG" /D "CURL_DISABLE_PROXY" /D "CURL_STATICLIB" /D "WIN32" /D "_MBCS" /D "CURL_DISABLE_LIBCURL_OPTION" /D "ALLOW_MSVC6_WITHOUT_PSDK" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 kernel32.lib user32.lib advapi32.lib gdi32.lib /nologo
# ADD LIB32 kernel32.lib user32.lib advapi32.lib gdi32.lib /nologo

!ENDIF 

# Begin Target

# Name "curl - Win32 Release"
# Name "curl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\amigaos.c
# End Source File
# Begin Source File

SOURCE=".\asyn-ares.c"
# End Source File
# Begin Source File

SOURCE=".\asyn-thread.c"
# End Source File
# Begin Source File

SOURCE=.\axtls.c
# End Source File
# Begin Source File

SOURCE=.\base64.c
# End Source File
# Begin Source File

SOURCE=.\bundles.c
# End Source File
# Begin Source File

SOURCE=.\conncache.c
# End Source File
# Begin Source File

SOURCE=.\connect.c
# End Source File
# Begin Source File

SOURCE=.\content_encoding.c
# End Source File
# Begin Source File

SOURCE=.\cookie.c
# End Source File
# Begin Source File

SOURCE=.\curl_addrinfo.c
# End Source File
# Begin Source File

SOURCE=.\curl_darwinssl.c
# End Source File
# Begin Source File

SOURCE=.\curl_fnmatch.c
# End Source File
# Begin Source File

SOURCE=.\curl_gethostname.c
# End Source File
# Begin Source File

SOURCE=.\curl_gssapi.c
# End Source File
# Begin Source File

SOURCE=.\curl_memrchr.c
# End Source File
# Begin Source File

SOURCE=.\curl_multibyte.c
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm.c
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm_core.c
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm_msgs.c
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm_wb.c
# End Source File
# Begin Source File

SOURCE=.\curl_rand.c
# End Source File
# Begin Source File

SOURCE=.\curl_rtmp.c
# End Source File
# Begin Source File

SOURCE=.\curl_sasl.c
# End Source File
# Begin Source File

SOURCE=.\curl_schannel.c
# End Source File
# Begin Source File

SOURCE=.\curl_sspi.c
# End Source File
# Begin Source File

SOURCE=.\curl_threads.c
# End Source File
# Begin Source File

SOURCE=.\cyassl.c
# End Source File
# Begin Source File

SOURCE=.\dict.c
# End Source File
# Begin Source File

SOURCE=.\easy.c
# End Source File
# Begin Source File

SOURCE=.\escape.c
# End Source File
# Begin Source File

SOURCE=.\file.c
# End Source File
# Begin Source File

SOURCE=.\fileinfo.c
# End Source File
# Begin Source File

SOURCE=.\formdata.c
# End Source File
# Begin Source File

SOURCE=.\ftp.c
# End Source File
# Begin Source File

SOURCE=.\ftplistparser.c
# End Source File
# Begin Source File

SOURCE=.\getenv.c
# End Source File
# Begin Source File

SOURCE=.\getinfo.c
# End Source File
# Begin Source File

SOURCE=.\gopher.c
# End Source File
# Begin Source File

SOURCE=.\gtls.c
# End Source File
# Begin Source File

SOURCE=.\hash.c
# End Source File
# Begin Source File

SOURCE=.\hmac.c
# End Source File
# Begin Source File

SOURCE=.\hostasyn.c
# End Source File
# Begin Source File

SOURCE=.\hostcheck.c
# End Source File
# Begin Source File

SOURCE=.\hostip.c
# End Source File
# Begin Source File

SOURCE=.\hostip4.c
# End Source File
# Begin Source File

SOURCE=.\hostip6.c
# End Source File
# Begin Source File

SOURCE=.\hostsyn.c
# End Source File
# Begin Source File

SOURCE=.\http.c
# End Source File
# Begin Source File

SOURCE=.\http_chunks.c
# End Source File
# Begin Source File

SOURCE=.\http_digest.c
# End Source File
# Begin Source File

SOURCE=.\http_negotiate.c
# End Source File
# Begin Source File

SOURCE=.\http_negotiate_sspi.c
# End Source File
# Begin Source File

SOURCE=.\http_proxy.c
# End Source File
# Begin Source File

SOURCE=.\idn_win32.c
# End Source File
# Begin Source File

SOURCE=.\if2ip.c
# End Source File
# Begin Source File

SOURCE=.\imap.c
# End Source File
# Begin Source File

SOURCE=.\inet_ntop.c
# End Source File
# Begin Source File

SOURCE=.\inet_pton.c
# End Source File
# Begin Source File

SOURCE=.\krb4.c
# End Source File
# Begin Source File

SOURCE=.\krb5.c
# End Source File
# Begin Source File

SOURCE=.\ldap.c
# End Source File
# Begin Source File

SOURCE=.\llist.c
# End Source File
# Begin Source File

SOURCE=.\md4.c
# End Source File
# Begin Source File

SOURCE=.\md5.c
# End Source File
# Begin Source File

SOURCE=.\memdebug.c
# End Source File
# Begin Source File

SOURCE=.\mprintf.c
# End Source File
# Begin Source File

SOURCE=.\multi.c
# End Source File
# Begin Source File

SOURCE=.\netrc.c
# End Source File
# Begin Source File

SOURCE=".\non-ascii.c"
# End Source File
# Begin Source File

SOURCE=.\nonblock.c
# End Source File
# Begin Source File

SOURCE=.\nss.c
# End Source File
# Begin Source File

SOURCE=.\openldap.c
# End Source File
# Begin Source File

SOURCE=.\parsedate.c
# End Source File
# Begin Source File

SOURCE=.\pingpong.c
# End Source File
# Begin Source File

SOURCE=.\polarssl.c
# End Source File
# Begin Source File

SOURCE=.\pop3.c
# End Source File
# Begin Source File

SOURCE=.\progress.c
# End Source File
# Begin Source File

SOURCE=.\qssl.c
# End Source File
# Begin Source File

SOURCE=.\rawstr.c
# End Source File
# Begin Source File

SOURCE=.\rtsp.c
# End Source File
# Begin Source File

SOURCE=.\security.c
# End Source File
# Begin Source File

SOURCE=.\select.c
# End Source File
# Begin Source File

SOURCE=.\sendf.c
# End Source File
# Begin Source File

SOURCE=.\share.c
# End Source File
# Begin Source File

SOURCE=.\slist.c
# End Source File
# Begin Source File

SOURCE=.\smtp.c
# End Source File
# Begin Source File

SOURCE=.\socks.c
# End Source File
# Begin Source File

SOURCE=.\socks_gssapi.c
# End Source File
# Begin Source File

SOURCE=.\socks_sspi.c
# End Source File
# Begin Source File

SOURCE=.\speedcheck.c
# End Source File
# Begin Source File

SOURCE=.\splay.c
# End Source File
# Begin Source File

SOURCE=.\ssh.c
# End Source File
# Begin Source File

SOURCE=.\sslgen.c
# End Source File
# Begin Source File

SOURCE=.\ssluse.c
# End Source File
# Begin Source File

SOURCE=.\strdup.c
# End Source File
# Begin Source File

SOURCE=.\strequal.c
# End Source File
# Begin Source File

SOURCE=.\strerror.c
# End Source File
# Begin Source File

SOURCE=.\strtok.c
# End Source File
# Begin Source File

SOURCE=.\strtoofft.c
# End Source File
# Begin Source File

SOURCE=.\telnet.c
# End Source File
# Begin Source File

SOURCE=.\tftp.c
# End Source File
# Begin Source File

SOURCE=.\timeval.c
# End Source File
# Begin Source File

SOURCE=.\transfer.c
# End Source File
# Begin Source File

SOURCE=.\url.c
# End Source File
# Begin Source File

SOURCE=.\version.c
# End Source File
# Begin Source File

SOURCE=.\warnless.c
# End Source File
# Begin Source File

SOURCE=.\wildcard.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\amigaos.h
# End Source File
# Begin Source File

SOURCE=.\arpa_telnet.h
# End Source File
# Begin Source File

SOURCE=.\asyn.h
# End Source File
# Begin Source File

SOURCE=.\axtls.h
# End Source File
# Begin Source File

SOURCE=.\bundles.h
# End Source File
# Begin Source File

SOURCE=".\config-win32.h"
# End Source File
# Begin Source File

SOURCE=.\conncache.h
# End Source File
# Begin Source File

SOURCE=.\connect.h
# End Source File
# Begin Source File

SOURCE=.\content_encoding.h
# End Source File
# Begin Source File

SOURCE=.\cookie.h
# End Source File
# Begin Source File

SOURCE=.\curl_addrinfo.h
# End Source File
# Begin Source File

SOURCE=.\curl_base64.h
# End Source File
# Begin Source File

SOURCE=.\curl_darwinssl.h
# End Source File
# Begin Source File

SOURCE=.\curl_fnmatch.h
# End Source File
# Begin Source File

SOURCE=.\curl_gethostname.h
# End Source File
# Begin Source File

SOURCE=.\curl_gssapi.h
# End Source File
# Begin Source File

SOURCE=.\curl_hmac.h
# End Source File
# Begin Source File

SOURCE=.\curl_ldap.h
# End Source File
# Begin Source File

SOURCE=.\curl_md4.h
# End Source File
# Begin Source File

SOURCE=.\curl_md5.h
# End Source File
# Begin Source File

SOURCE=.\curl_memory.h
# End Source File
# Begin Source File

SOURCE=.\curl_memrchr.h
# End Source File
# Begin Source File

SOURCE=.\curl_multibyte.h
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm.h
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm_core.h
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm_msgs.h
# End Source File
# Begin Source File

SOURCE=.\curl_ntlm_wb.h
# End Source File
# Begin Source File

SOURCE=.\curl_rand.h
# End Source File
# Begin Source File

SOURCE=.\curl_rtmp.h
# End Source File
# Begin Source File

SOURCE=.\curl_sasl.h
# End Source File
# Begin Source File

SOURCE=.\curl_schannel.h
# End Source File
# Begin Source File

SOURCE=.\curl_setup.h
# End Source File
# Begin Source File

SOURCE=.\curl_setup_once.h
# End Source File
# Begin Source File

SOURCE=.\curl_sspi.h
# End Source File
# Begin Source File

SOURCE=.\curl_threads.h
# End Source File
# Begin Source File

SOURCE=.\curlx.h
# End Source File
# Begin Source File

SOURCE=.\cyassl.h
# End Source File
# Begin Source File

SOURCE=.\dict.h
# End Source File
# Begin Source File

SOURCE=.\easyif.h
# End Source File
# Begin Source File

SOURCE=.\escape.h
# End Source File
# Begin Source File

SOURCE=.\file.h
# End Source File
# Begin Source File

SOURCE=.\fileinfo.h
# End Source File
# Begin Source File

SOURCE=.\formdata.h
# End Source File
# Begin Source File

SOURCE=.\ftp.h
# End Source File
# Begin Source File

SOURCE=.\ftplistparser.h
# End Source File
# Begin Source File

SOURCE=.\getinfo.h
# End Source File
# Begin Source File

SOURCE=.\gopher.h
# End Source File
# Begin Source File

SOURCE=.\gtls.h
# End Source File
# Begin Source File

SOURCE=.\hash.h
# End Source File
# Begin Source File

SOURCE=.\hostcheck.h
# End Source File
# Begin Source File

SOURCE=.\hostip.h
# End Source File
# Begin Source File

SOURCE=.\http.h
# End Source File
# Begin Source File

SOURCE=.\http_chunks.h
# End Source File
# Begin Source File

SOURCE=.\http_digest.h
# End Source File
# Begin Source File

SOURCE=.\http_negotiate.h
# End Source File
# Begin Source File

SOURCE=.\http_proxy.h
# End Source File
# Begin Source File

SOURCE=.\if2ip.h
# End Source File
# Begin Source File

SOURCE=.\imap.h
# End Source File
# Begin Source File

SOURCE=.\inet_ntop.h
# End Source File
# Begin Source File

SOURCE=.\inet_pton.h
# End Source File
# Begin Source File

SOURCE=.\krb4.h
# End Source File
# Begin Source File

SOURCE=.\llist.h
# End Source File
# Begin Source File

SOURCE=.\memdebug.h
# End Source File
# Begin Source File

SOURCE=.\multihandle.h
# End Source File
# Begin Source File

SOURCE=.\multiif.h
# End Source File
# Begin Source File

SOURCE=.\netrc.h
# End Source File
# Begin Source File

SOURCE=".\non-ascii.h"
# End Source File
# Begin Source File

SOURCE=.\nonblock.h
# End Source File
# Begin Source File

SOURCE=.\nssg.h
# End Source File
# Begin Source File

SOURCE=.\parsedate.h
# End Source File
# Begin Source File

SOURCE=.\pingpong.h
# End Source File
# Begin Source File

SOURCE=.\polarssl.h
# End Source File
# Begin Source File

SOURCE=.\pop3.h
# End Source File
# Begin Source File

SOURCE=.\progress.h
# End Source File
# Begin Source File

SOURCE=.\qssl.h
# End Source File
# Begin Source File

SOURCE=.\rawstr.h
# End Source File
# Begin Source File

SOURCE=.\rtsp.h
# End Source File
# Begin Source File

SOURCE=.\select.h
# End Source File
# Begin Source File

SOURCE=.\sendf.h
# End Source File
# Begin Source File

SOURCE=".\setup-vms.h"
# End Source File
# Begin Source File

SOURCE=.\share.h
# End Source File
# Begin Source File

SOURCE=.\slist.h
# End Source File
# Begin Source File

SOURCE=.\smtp.h
# End Source File
# Begin Source File

SOURCE=.\sockaddr.h
# End Source File
# Begin Source File

SOURCE=.\socks.h
# End Source File
# Begin Source File

SOURCE=.\speedcheck.h
# End Source File
# Begin Source File

SOURCE=.\splay.h
# End Source File
# Begin Source File

SOURCE=.\ssh.h
# End Source File
# Begin Source File

SOURCE=.\sslgen.h
# End Source File
# Begin Source File

SOURCE=.\ssluse.h
# End Source File
# Begin Source File

SOURCE=.\strdup.h
# End Source File
# Begin Source File

SOURCE=.\strequal.h
# End Source File
# Begin Source File

SOURCE=.\strerror.h
# End Source File
# Begin Source File

SOURCE=.\strtok.h
# End Source File
# Begin Source File

SOURCE=.\strtoofft.h
# End Source File
# Begin Source File

SOURCE=.\telnet.h
# End Source File
# Begin Source File

SOURCE=.\tftp.h
# End Source File
# Begin Source File

SOURCE=.\timeval.h
# End Source File
# Begin Source File

SOURCE=.\transfer.h
# End Source File
# Begin Source File

SOURCE=.\url.h
# End Source File
# Begin Source File

SOURCE=.\urldata.h
# End Source File
# Begin Source File

SOURCE=.\warnless.h
# End Source File
# Begin Source File

SOURCE=.\wildcard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libcurl.rc
# End Source File
# End Group
# End Target
# End Project
