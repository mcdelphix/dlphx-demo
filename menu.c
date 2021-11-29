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

/* verifyDB.sh */
#define SHELLSCRIPT2 "\
#!/bin/sh\n\n\
echo \"ORACLE_SID=orasrc1 voradev1 vora1 voramsk1 voraqa1\"\n\
export ORAENV_ASK=NO\n\
export ORACLE_HOME=/u01/app/oracle/product/18.0.0/dbhome_1\n\
export PATH=$PATH:$ORACLE_HOME/bin\n\
# . oraenv\n\
export ORAENV_ASK=YES\n\
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

/* orainfo.sql */

#define SHELLSCRIPT4 "\
col name format a50\n\
col value format a40\n\
col name_val format a90\n\
col tablespace_name format a20\n\
col file_name format a45\n\
col status format a15\n\
col member format a45\n\
col type format a20\n\
col status format a10\n\
col instance_name format a10\n\
col host_name format a10\n\
col db_unique_name format a10\n\
col database_status format a10\n\
col version format a10\n\
col number_of_files format 9,999\n\
set pagesize 500\n\
set linesize 100\n\
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

/* verifyDB.sql */

#define SHELLSCRIPT5 "\
set pagesize 100\n\
set linesize 100\n\
set echo off\n\
set feedback off\n\
set wrap on\n\
col name format a15\n\
col owner format a30\n\
col restricted format a10\n\
col open_time format a30\n\
col tablespace_name format a15\n\
col file_name format a75\n\
select distinct tablespace_name, file_name from dba_data_files order by 1;\n\
select owner,count(*) from dba_tables group by owner order by 1;\n\
select dbid, name, open_mode from v$database;\n\
select sum(bytes)/(1024*1024*1024) \"dbSize (GB)\" from dba_data_files;\n\
select * from v$instance;\n\
select cdb from v$database;\n\
select name, con_id, dbid, con_uid from v$containers;\n\
select name, open_mode, restricted, open_time from v$pdbs;\n\
exit\n\
"

/* watch4mount.sh */
#define SHELLSCRIPT6 "\
#!/bin/bash\n\n\
watch 'ps -ef | grep pmon | grep -v grep ; echo \"\"; echo \"\"; df -h'\n\
"

/* query.sql */
#define SHELLSCRIPT7 "\
set pagesize 100\n\
set linesize 140\n\
col patient_id format 9999 heading PAT_ID\n\
col employee_id format 9999\n\
col first_name format a15\n\
col last_name format a15\n\
col firstname format a15\n\
col lastname format a15\n\
col address format a30\n\
col dept_name format a25\n\
col zipcode format a10\n\
col email format a25\n\
col city format a15\n\
select employee_id, first_name, last_name, dept_name, city from employees;\n\
select patient_id, firstname, lastname, address, city, zipcode, email from patient;\n\
exit\n\
"

/* query.sh */
#define SHELLSCRIPT8 "\
#!/bin/sh\n\n\
echo \"ORACLE_SID=orasrc1 voradev1 vora1 voramsk1 voraqa1\"\n\
export ORACLE_HOME=/u01/app/oracle/product/18.0.0/dbhome_1\n\
export PATH=$PATH:$ORACLE_HOME/bin\n\
sqlplus delphixdb/delphixdb @query.sql\n\
"

/* action.sh */
#define SHELLSCRIPT9 "\
#!/bin/sh\n\n\
list_rows()\n\
{\n\
sqlplus / as sysdba <<EOF\n\
set pagesize 100\n\
set linesize 100\n\
set echo off\n\
set feedback off\n\
set wrap on\n\
col TTLE format a40 heading 'INSERT DATE - DD-MON-YY HH24:MI:SS'\n\
select trans_id, to_char(trans_ts, 'DD-MON-YY HH24:MI:SS') TTLE from TransTAB;\n\
exit\n\
EOF\n\
}\n\n\
ins_rows()\n\
{\n\
sqlplus / as sysdba <<EOF\n\
insert into TransTAB values (trans_id_seq.nextval, SYSDATE);\n\
commit\n\
exit\n\
EOF\n\
}\n\n\
cleanTransTAB()\n\
{\n\
sqlplus / as sysdba <<EOF\n\
drop sequence trans_id_seq;\n\
DROP TABLE TransTAB;\n\
commit\n\
exit\n\
EOF\n\
}\n\n\
initTransTAB()\n\
{\n\
sqlplus / as sysdba <<EOF\n\
create sequence trans_id_seq start with 1 increment by 1 nocache;\n\
CREATE TABLE TransTAB\n\
(\n\
    trans_id integer,\n\
    trans_ts DATE\n\
);\n\
commit\n\
exit\n\
EOF\n\
}\n\n\
# initTransTAB\n\
# ins_rows\n\
# list_rows\n\
# cleanTransTAB\n\
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


const char *ora_str = "create user act_rman_user identified by password;\n\
lsnrctl reload\n\
lsnrctl status\n\
source 10.0.1.20 delphix db-delphixdb , orasrc1\n\
target 10.0.1.30 delphix db-delphixdb \n\
orapwd file=$ORACLE_HOME/dbs/orapwacmetest password=oracle\n\
select * from global_name;\n\
grant create session, resource, sysdba to act_rman_user;\n";

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
   
   system("mkdir -p scripts");
   create_file("scripts/t.sh", (char *) script1);
   create_file("scripts/x.sh", SHELLSCRIPT3);
   create_file("scripts/count.sh", SHELLSCRIPT1);
   create_file("scripts/verifyDB.sh", SHELLSCRIPT2);
   create_file("scripts/verifyDB.sql", SHELLSCRIPT5);
   create_file("scripts/orainfo.sql", SHELLSCRIPT4);
   create_file("scripts/watch4mount.sh", SHELLSCRIPT6);
   create_file("scripts/query.sql", SHELLSCRIPT7);
   create_file("scripts/query.sh", SHELLSCRIPT8);
   create_file("scripts/action.sh", SHELLSCRIPT9);

   printf("Hello world\n");

   system("id");
   system("/bin/bash /home/delphix/scripts/count.sh");

   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_b()
{
   system("clear");
   printf("You have selected option B - run remote commands \n");
   printf("Oracle instances running on 10.0.1.30 :\n");
   system("ssh -o LogLevel=ERROR 10.0.1.30 \"ps -ef | grep pmon | grep -v grep\"");
   printf("Oracle instances running on 10.0.1.20 :\n");
   system("ssh -o LogLevel=ERROR 10.0.1.20 \"ps -ef | grep pmon | grep -v grep\"");
   printf("Copies orainfo.sql to 10.0.1.20 :-\n");
   system("scp scripts/orainfo.sql 10.0.1.20:/tmp/orainfo.sql");
   printf("chmod 755 orainfo.sql :-\n");
   system("ssh -o LogLevel=ERROR 10.0.1.20 \"chmod 755 /tmp/orainfo.sql\""); 
   printf("ls -la orainfo.sql :-\n");
   system("ssh -o LogLevel=ERROR 10.0.1.20 \"ls -la /tmp/orainfo.sql\""); 
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_c()
{
   system("clear");
   printf("You have selected option C - connecting as root \n");
   printf("ssh centos@10.0.1.20\n");  
   printf("sudo su -\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_d()
{
   system("clear");
   printf("You have selected option D - oracle stuff\n");
   printf("%s", (char *) ora_str);
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_e()
{
   system("clear");
   printf("You have selected option E - connecting to Oracle source\n");
   system("ssh 10.0.1.20");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_f()
{
   system("clear");
   printf("You have selected option F - connecting to Oracle target\n");
   system("ssh 10.0.1.30");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_g()
{
   system("clear");
   printf("You have selected option G - prepare Oracle source\n");
   system("scp scripts/verifyDB.sql 10.0.1.20:/home/delphix/verifyDB.sql");
   system("scp scripts/verifyDB.sh 10.0.1.20:/home/delphix/verifyDB.sh");
   system("ssh -o LogLevel=ERROR 10.0.1.20 \"chmod 755 /home/delphix/verifyDB.sh\"");
   system("scp scripts/orainfo.sql 10.0.1.20:/home/delphix/orainfo.sql");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_h()
{
   system("clear");
   printf("You have selected option H - prepare Oracle target\n");
   system("scp scripts/verifyDB.sql 10.0.1.30:/home/delphix/verifyDB.sql");
   system("scp scripts/verifyDB.sh 10.0.1.30:/home/delphix/verifyDB.sh");
   system("ssh -o LogLevel=ERROR 10.0.1.30 \"chmod 755 /home/delphix/verifyDB.sh\"");
   system("scp scripts/orainfo.sql 10.0.1.30:/home/delphix/orainfo.sql");
   system("scp scripts/watch4mount.sh 10.0.1.30:/home/delphix/watch4mount.sh");
   system("ssh -o LogLevel=ERROR 10.0.1.30 \"chmod 755 /home/delphix/watch4mount.sh\"");
   system("scp scripts/query.sql 10.0.1.30:/home/delphix/query.sql");
   system("scp scripts/query.sh 10.0.1.30:/home/delphix/query.sh");
   system("ssh -o LogLevel=ERROR 10.0.1.30 \"chmod 755 /home/delphix/query.sh\"");
   system("scp scripts/query.sh 10.0.1.30:/home/delphix/action.sh");
   system("ssh -o LogLevel=ERROR 10.0.1.30 \"chmod 755 /home/delphix/action.sh\"");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_j()
{
   system("clear");
   printf("You have selected option J\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_k()
{
   system("clear");
   printf("You have selected option K\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void list_menu_options()
{
   system("clear");
   printf("\nMenu Options\n");
   printf("------------------------------------------------------\n");
   printf("a: Option A - create scripts \n");
   printf("b: Option B - run remote commands \n");
   printf("c: Option C - connecting as root \n");   
   printf("d: Option D - Oracle stuff\n");
   printf("e: Option E - connect to Oracle source\n");
   printf("f: Option F - connect to Oracle target\n");
   printf("g: Option G - prepare Oracle source\n");
   printf("h: Option H - prepare Oracle target\n");
   printf("j: Option J\n");
   printf("k: Option K\n");
   printf("z: Save and quit\n");
   printf("\n\nPlease enter a choice (a, b, c, d, e, f, g, h, j, k or z) ---> ");
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
         case 'h':
            process_option_h();
            break;
         case 'j':
            process_option_j();
            break;
         case 'k':
            process_option_k();
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