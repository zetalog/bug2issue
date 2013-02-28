# Microsoft Developer Studio Project File - Name="mysql" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mysql - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mysql.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mysql.mak" CFG="mysql - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mysql - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mysql - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mysql - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\bin\release"
# PROP BASE Intermediate_Dir "..\..\..\obj\release\mysql"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\bin\release"
# PROP Intermediate_Dir "..\..\..\obj\release\mysql"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O2 /I "..\..\..\include" /I "..\include" /D "DBUG_OFF" /D "NDEBUG" /D "MYSQL_CLIENT" /D "_WINDOWS" /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "mysql - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\bin\debug"
# PROP BASE Intermediate_Dir "..\..\..\obj\debug\mysql"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\bin\debug"
# PROP Intermediate_Dir "..\..\..\obj\debug\mysql"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Z7 /Od /I "..\..\..\include" /I "..\include" /D "_DEBUG" /D "SAFEMALLOC" /D "SAFE_MUTEX" /D "MYSQL_CLIENT" /D "_WINDOWS" /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "mysql - Win32 Release"
# Name "mysql - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=.\mysys\array.c
# End Source File
# Begin Source File

SOURCE=.\strings\bchange.c
# End Source File
# Begin Source File

SOURCE=.\strings\bmove.c
# End Source File
# Begin Source File

SOURCE=.\strings\bmove_upp.c
# End Source File
# Begin Source File

SOURCE=".\mysys\charset-def.c"
# End Source File
# Begin Source File

SOURCE=.\mysys\charset.c
# End Source File
# Begin Source File

SOURCE=.\client.c
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-big5.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-bin.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-cp932.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-czech.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-euc_kr.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-extra.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-gb2312.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-gbk.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-latin1.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-mb.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-simple.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-sjis.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-tis620.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-uca.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-ucs2.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-ujis.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-utf8.c"
# End Source File
# Begin Source File

SOURCE=".\strings\ctype-win1250ch.c"
# End Source File
# Begin Source File

SOURCE=.\strings\ctype.c
# End Source File
# Begin Source File

SOURCE=.\dbug\dbug.c
# End Source File
# Begin Source File

SOURCE=.\mysys\default.c
# End Source File
# Begin Source File

SOURCE=.\errmsg.c
# End Source File
# Begin Source File

SOURCE=.\mysys\errors.c
# End Source File
# Begin Source File

SOURCE=.\get_password.c
# End Source File
# Begin Source File

SOURCE=.\strings\int2str.c
# End Source File
# Begin Source File

SOURCE=.\strings\is_prefix.c
# End Source File
# Begin Source File

SOURCE=.\libmysql.c
# End Source File
# Begin Source File

SOURCE=.\mysys\list.c
# End Source File
# Begin Source File

SOURCE=.\strings\llstr.c
# End Source File
# Begin Source File

SOURCE=.\strings\longlong2str.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_cache.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_dirname.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_fn_ext.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_format.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_iocache.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_iocache2.c

!IF  "$(CFG)" == "mysql - Win32 Release"

!ELSEIF  "$(CFG)" == "mysql - Win32 Debug"

# ADD CPP /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mysys\mf_loadpath.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_pack.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_path.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_tempfile.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_unixpath.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mf_wcomp.c
# End Source File
# Begin Source File

SOURCE=.\mysys\mulalloc.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_access.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_alloc.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_compress.c
# ADD CPP /I "../zlib"
# End Source File
# Begin Source File

SOURCE=.\mysys\my_create.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_delete.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_div.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_error.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_file.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_fopen.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_fstream.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_gethostbyname.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_getopt.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_getwd.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_init.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_lib.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_malloc.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_messnc.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_net.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_once.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_open.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_pread.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_pthread.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_read.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_realloc.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_rename.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_seek.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_static.c
# End Source File
# Begin Source File

SOURCE=.\strings\my_strtoll10.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_symlink.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_symlink2.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_tempnam.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_thr_init.c
# End Source File
# Begin Source File

SOURCE=.\my_time.c
# End Source File
# Begin Source File

SOURCE=.\strings\my_vsnprintf.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_wincond.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_winthread.c
# End Source File
# Begin Source File

SOURCE=.\mysys\my_write.c
# End Source File
# Begin Source File

SOURCE=.\mysys_priv.h
# End Source File
# Begin Source File

SOURCE=.\net_serv.c
# End Source File
# Begin Source File

SOURCE=.\pack.c
# End Source File
# Begin Source File

SOURCE=.\password.c
# End Source File
# Begin Source File

SOURCE=.\mysys\safemalloc.c
# End Source File
# Begin Source File

SOURCE=.\mysys\sha1.c
# End Source File
# Begin Source File

SOURCE=.\strings\str2int.c
# End Source File
# Begin Source File

SOURCE=.\strings\strcend.c
# End Source File
# Begin Source File

SOURCE=.\strings\strcont.c
# End Source File
# Begin Source File

SOURCE=.\strings\strend.c
# End Source File
# Begin Source File

SOURCE=.\strings\strfill.c
# End Source File
# Begin Source File

SOURCE=.\mysys\string.c
# End Source File
# Begin Source File

SOURCE=.\strings\strinstr.c
# End Source File
# Begin Source File

SOURCE=.\strings\strmake.c
# End Source File
# Begin Source File

SOURCE=.\strings\strmov.c
# End Source File
# Begin Source File

SOURCE=.\strings\strnlen.c
# End Source File
# Begin Source File

SOURCE=.\strings\strnmov.c
# End Source File
# Begin Source File

SOURCE=.\strings\strtod.c
# End Source File
# Begin Source File

SOURCE=.\strings\strtoll.c
# End Source File
# Begin Source File

SOURCE=.\strings\strtoull.c
# End Source File
# Begin Source File

SOURCE=.\strings\strxmov.c
# End Source File
# Begin Source File

SOURCE=.\strings\strxnmov.c
# End Source File
# Begin Source File

SOURCE=.\mysys\thr_mutex.c
# End Source File
# Begin Source File

SOURCE=.\mysys\typelib.c
# End Source File
# Begin Source File

SOURCE=.\vio\vio.c
# End Source File
# Begin Source File

SOURCE=.\vio\viosocket.c
# End Source File
# Begin Source File

SOURCE=.\vio\viossl.c
# End Source File
# Begin Source File

SOURCE=.\vio\viosslfactories.c
# End Source File
# Begin Source File

SOURCE=.\strings\xml.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\client_settings.h
# End Source File
# Begin Source File

SOURCE="..\include\config-win.h"
# End Source File
# Begin Source File

SOURCE=..\include\errmsg.h
# End Source File
# Begin Source File

SOURCE=..\include\help_end.h
# End Source File
# Begin Source File

SOURCE=..\include\help_start.h
# End Source File
# Begin Source File

SOURCE=..\include\m_ctype.h
# End Source File
# Begin Source File

SOURCE=..\include\m_string.h
# End Source File
# Begin Source File

SOURCE=..\include\my_alarm.h
# End Source File
# Begin Source File

SOURCE=..\include\my_alloc.h
# End Source File
# Begin Source File

SOURCE=..\include\my_base.h
# End Source File
# Begin Source File

SOURCE=..\include\my_dbug.h
# End Source File
# Begin Source File

SOURCE=..\include\my_dir.h
# End Source File
# Begin Source File

SOURCE=..\include\my_getopt.h
# End Source File
# Begin Source File

SOURCE=..\include\my_global.h
# End Source File
# Begin Source File

SOURCE=..\include\my_list.h
# End Source File
# Begin Source File

SOURCE=..\include\my_net.h
# End Source File
# Begin Source File

SOURCE=..\include\my_pthread.h
# End Source File
# Begin Source File

SOURCE=.\mysys\my_static.h
# End Source File
# Begin Source File

SOURCE=..\include\my_sys.h
# End Source File
# Begin Source File

SOURCE=..\include\my_time.h
# End Source File
# Begin Source File

SOURCE=..\include\my_xml.h
# End Source File
# Begin Source File

SOURCE=..\include\mysql.h
# End Source File
# Begin Source File

SOURCE=..\include\mysql_com.h
# End Source File
# Begin Source File

SOURCE=..\include\mysql_embed.h
# End Source File
# Begin Source File

SOURCE=..\include\mysql_time.h
# End Source File
# Begin Source File

SOURCE=..\include\mysql_version.h
# End Source File
# Begin Source File

SOURCE=..\include\mysqld_error.h
# End Source File
# Begin Source File

SOURCE=..\include\mysys_err.h
# End Source File
# Begin Source File

SOURCE=.\mysys\mysys_priv.h
# End Source File
# Begin Source File

SOURCE=..\include\raid.h
# End Source File
# Begin Source File

SOURCE=..\include\sha1.h
# End Source File
# Begin Source File

SOURCE=..\include\sql_common.h
# End Source File
# Begin Source File

SOURCE=.\strings\t_ctype.h
# End Source File
# Begin Source File

SOURCE=..\include\thr_alarm.h
# End Source File
# Begin Source File

SOURCE=..\include\typelib.h
# End Source File
# Begin Source File

SOURCE=.\vio\vio_priv.h
# End Source File
# Begin Source File

SOURCE=..\include\violite.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\strings\strto.c
# PROP Exclude_From_Build 1
# End Source File
# End Target
# End Project
