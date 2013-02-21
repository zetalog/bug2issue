1. Install mysql-essential, the tested version is 6.0.0-alpha
   Before installation, you need to
   1.1 add an exception port 3306 into Windows Firewall setting.
   1.2 run cmd.exe as administrator
   1.3 lauch mysql-essential-6.0.0-alpha-win32.msi in the priviledged cmd.exe
2. Install mysql-query-browser, the tested version is 1.1.20
   2.1 lauch mysql-query-browser-1.1.20-win.msi
3. Restore mysql database
   3.1 lauch mysql in the cmd.exe (you should already have it in the PATH environment in the step 1.3)
       mysql -u root --password=<mysql root password>
   3.2 restore mysql database using backup sql file
       mysql> create database acpica;
       mysql> use acpica;
       mysql> source <backup sql file>;
4. Dump bugzilla entries
   4.1 compile bug2issue
   4.2 dump issues:
       bug2issue -d acpica -w <mysql root password> <path to store issue files>
   4.3 dump comments:
       bug2issue -d acpica -w <mysql root password> -c <path to store issue files>
