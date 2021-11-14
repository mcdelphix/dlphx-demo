#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
cd c
cp /mnt/c/tmp/menu.c .
cc -o menu.exe menu.c
*/

#define SHELLSCRIPT1 "\
#!/bin/bash\n\n\
for ((i=0 ; i < 10 ; i++))\n\
do\n\
echo \"Count: $i\"\n\
done\n\
"

#define SHELLSCRIPT2 "\
#!/bin/sh\n\n\
export ORACLE_HOME=/home/oracle/app/oracle/product/11.2.0/dbhome_1\n\
export PATH=$ORACLE_HOME:$PATH\n\
sqlplus / as sysdba @verifyDB.sql\n\
"

#define SHELLSCRIPT3 "\
#!/bin/bash\n\n\
oracleSID=$1\n\
srcHOST=$2\n\n\
parmFILE=\"/tmp/qry.sql\"\n\
cat > $parmFILE <<eot\n\
set pagesize 100\n\
set linesize 100\n\
set pages 0 echo off\n\
set feedback off\n\
set wrap on\n\
col tablespace_name format a15\n\
col file_name format a75\n\
connect / as sysdba\n\
select distinct tablespace_name, file_name from dba_data_files order by 1;\n\
select 'Status of the Running Instance:' from dual;\n\
exit\n\
eot\n\
"

#define SHELLSCRIPT4 "\
col name format a50\n\
col value format a60\n\
col name_val format a90\n\
col tablespace_name format a20\n\
col file_name format a45\n\
col status format a15\n\
col member format a45\n\
col type format a8\n\
col status format a10\n\
col instance_name format a10\n\
col host_name format a10\n\
col db_unique_name format a10\n\
col database_status format a10\n\
col version format a10\n\
col number_of_files format 9,999\n\
set pagesize 500\n\
set linesize 90\n\
set termout on\n\
set feedback off\n\
col value format 9,999,999,999\n\n\
spool ora-info.lis\n\
# column today NEW_VALUE p_currdate noprint\n\
select TO_CHAR(SYSDATE,'fmMonth ddth, yyyy') today from dual;\n\
select   'Database Name (SID): ' || name \"name\" from v$database;\n\
select ora_database_name from dual;\n\
select name || ' - ' || value name_val from v$parameter order by name_val;\n\
select tablespace_name, status from dba_tablespaces;\n\
select tablespace_name, file_name, status, bytes/1024/1024/1024 \"in GB\" from dba_data_files;\n\
select sum(bytes)/(1024*1024*1024) \"DBsize in GB\" from dba_data_files;\n\
select sum(blocks*block_size)/(1024*1024*1024) \"LOGsize in GB\" from v$archived_log where deleted = 'NO';\n\
select tablespace_name, file_name, status from dba_temp_files;\n\
select member, type, status from v$logfile;\n\
select name, status, block_size, file_size_blks from v$controlfile;\n\
select name from v$archived_log;\n\
select name from v$recovery_file_dest;\n\
select directory_name, directory_path from dba_directories;\n\
select name, value, unit from V$PGASTAT;\n\
select name, value from v$sga;\n\
select banner from v$version;\n\
SELECT * FROM V$DIAG_INFO;\n\
select instance_name, host_name, version, status, logins, database_status, instance_role, active_state from v$instance;\n\
select name, created, sysdate, log_mode, controlfile_type, open_mode, protection_mode, database_role, db_unique_name, platform_name from v$database;\n\
select name, floor(space_limit / 1024 / 1024) \"Size MB\", ceil(space_used / 1024 / 1024) \"Used MB\", number_of_files from v$recovery_file_dest;\n\
select file_type, number_of_files from v$recovery_area_usage;\n\
select filename, status BCT_status, bytes from v$block_change_tracking;\n\
show parameter target;\n\
show sga;\n\
select name, value/1024/1024 \"in MB\" from v$pgastat where name in ('total PGA allocated','maximum PGA allocated');\n\
select decode( grouping(nm), 1, 'total', nm ) nm, round(sum(val/1024/1024)) mb\n\
from ( select 'sga' nm, sum(value) val from v$sga union all select 'pga', sum(a.value) from v$sesstat a, v$statname b where b.name = 'session pga memory' and a.statistic# = b.statistic#) group by rollup(nm);\n\
select 'Total System Global Area :' hd1, sum(value) sgatot, 'bytes' hd2 from  v$sga;\n\
exit\n\
"

const char *script1 = "#!/bin/bash\n\n\
[ $# -ne $numparms ] && usage\n\n\
oracleSID=$1\n\
SRCHOST=$2\n\
readonly PARMFILE=\"/tmp/z_qry.sql\"\n\
cat > $PARMFILE <<EOT\n\
set pagesize 100\n\
set linesize 100\n\
set pages 0 echo off\n\
set feedback off\n\
set wrap on\n\
select sum(bytes)/(1024*1024*1024) \"dbSize (GB)\" from dba_data_files;\n\
select * from v$database_incarnation;\n\
exit\n\
EOT\n\n\
scp -P 22  -i ~/.ssh/id_rsa $PARMFILE root@$SRCHOST:$PARMFILE 2>&- > /dev/null\n\
ssh -t -t -p 22 -i ~/.ssh/id_rsa root@$SRCHOST \"chown oracle:oinstall $PARMFILE\" 2>&- > /dev/null\n\
ssh -t -t -p 22 -i ~/.ssh/id_rsa root@$SRCHOST \"chmod 644 $PARMFILE\" 2>&- > /dev/null\n\
ssh -t -t -p 22 -i ~/.ssh/id_rsa root@$SRCHOST \"sudo su - oracle -c 'export ORACLE_SID=$oracleSID;export ORAENV_ASK=NO;. /usr/local/bin/oraenv; sqlplus -s /nolog' < $PARMFILE\"\n\
exit 0";

void create_file(char *filename, char *buf) 
{
   FILE *fptr;

   fptr = fopen(filename, "w");
   fprintf(fptr, "%s", buf);
   fclose(fptr);
}

void process_option_a()
{
   system("clear");
   printf("You have selected option A - creating files\n");
   
   create_file("t.sh", (char *) script1);
   create_file("x.sh", SHELLSCRIPT3);
   create_file("y.sh", SHELLSCRIPT2);
   create_file("orainfo.sql", SHELLSCRIPT4);

   printf("Hello world\n");

   system("id");
   system("/bin/bash /root/c/x.sh");

   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_b()
{
   system("clear");
   printf("You have selected option B - run remote commands \n");
   system("ssh 10.0.1.20 \"ps -ef | grep pmon\"");
   system("scp orainfo.sql 10.0.1.20:/tmp/orainfo.sql");
   system("ssh 10.0.1.20 \"chmod 755 /tmp/orainfo.sql\""); 
   system("ssh 10.0.1.20 \"ls -la /tmp/orainfo.sql\""); 
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_c()
{
   system("clear");
   printf("You have selected option C\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_d()
{
   system("clear");
   printf("You have selected option D\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_e()
{
   system("clear");
   printf("You have selected option E\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_f()
{
   system("clear");
   printf("You have selected option D\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_g()
{
   system("clear");
   printf("You have selected option E\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void list_menu_options()
{
   system("clear");
   printf("\nMenu Options\n");
   printf("------------------------------------------------------\n");
   printf("a: Option A - create scripts\n");
   printf("b: Option B - run remote commands \n");
   printf("c: Option C\n");   
   printf("d: Option D\n");
   printf("e: Option E\n");
   printf("f: Option F\n");
   printf("g: Option G\n");   
   printf("z: Save and quit\n");
   printf("\n\nPlease enter a choice (a, b, c, d, e, f, g, or z) ---> ");
}

void process_menu()
{
   char ch;

   do {
      list_menu_options();
      ch = tolower(getchar());  // read a char, convert to lower case
      getchar();                // clear the newline char
      switch(ch) {
         case 'a':
            process_option_a();
            break;
         case 'b':
            process_option_b();
            break;
         case 'c':
            process_option_c();
            break;
         case 'd':
            process_option_d();
            break;
         case 'e':
            process_option_e();
            break;                        
         case 'f':
            process_option_f();
            break;
         case 'g':
            process_option_g();
            break;
         case 'z':
            break;
         default:
            printf("\nError: Invalid Input.  Please try again...");
            break;
       }
    } while (ch != 'z');
}


void main()
{
   process_menu();

/*
  ssh centos@10.0.1.20
  sudo su -

  /home/delphix

  ssh 10.0.1.20  -  orasrc1
  ssh 10.0.1.30  -  target
 /01/app/oracle/product/18.0.0/dbhome_1

  system("ssh -t user@remote sh /<remote>home/user/<file_name>.sh");
  system("scp user@remote:/path/to/remote_file /path/to/local_ fptr = fopen("x.sh", "w");
*/
}