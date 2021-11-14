#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void process_option_a()
{
   system("clear");
   printf("You have selected option A\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void process_option_b()
{
   system("clear");
   printf("You have selected option B\n");
   printf("Enter to return to main menu\n");
   getchar();
}

void list_menu_options()
{
   system("clear");
   printf("\nMenu Options\n");
   printf("------------------------------------------------------\n");
   printf("a: Option A\n");
   printf("b: Option B\n");
   printf("z: Save and quit\n");
   printf("\n\nPlease enter a choice (a, b, or z) ---> ");
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
   FILE *fptr;

   fptr = fopen("t.sh", "w");
   fprintf(fptr, "%s", script1);
   fclose(fptr);

   printf("Hello world\n");
   fptr = fopen("x.sh", "w");
   fprintf(fptr, "%s", SHELLSCRIPT3);
   fclose(fptr);

   fptr = fopen("y.sh", "w");
   fprintf(fptr, "%s", SHELLSCRIPT2);
   fclose(fptr);

   system("id");
   system("/bin/bash /root/c/x.sh");

   printf("Enter to return to main menu\n");
   getchar();
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