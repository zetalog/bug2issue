
                            BUG2ISSUE Win32 README

Bug2issue is developed to help open source communities to convert bugzilla
bugs into github issues.

This README file contains informations required to use bug2issue on win32
platforms.

1. Install mysql-essential, the tested version is 6.0.0-alpha
   Before installation, you need to
   1.1 add an exception port 3306 into Windows Firewall setting.
   1.2 run cmd.exe as administrator
   1.3 lauch mysql-essential-6.0.0-alpha-win32.msi in the priviledged cmd.exe
2. Install mysql-query-browser, the tested version is 1.1.20
   2.1 lauch mysql-query-browser-1.1.20-win.msi
3. Restore mysql database
   3.1 lauch mysql in the cmd.exe (you should already have it in the PATH
       environment in the step 1.3)
       mysql -u root --password=<mysql root password>
   3.2 restore mysql database using backup sql file
       mysql> create database acpica;
       mysql> use acpica;
       mysql> source <backup sql file>;
4. Compile bug2issue win32 binary
   4.1 compile bug2issue
       MSVC project files need to be converted before compiling win32 version:
       ./scripts/msvcenable.sh .
   4.2 generate bug2issue patches
       The reversal can be done before generating patches:
       ./scripts/msvcenable.sh -r .
5. Use bug2issue win32 binary
   5.1 dump issues and comments (-c) into local folder as json format:
       bug2issue -c -d acpica -u <root:mysql password> \
                 -f <path to store files>
   5.2 export issues and comments (-c) to github.com:
       bug2issue -c -d acpica -u <root:mysql password> \
                 -r <github repo> -w <github user:github password>

