$SqlInstance="WIN2016TARGETA"
$backupFile="C:\Backups\Empdb.bak"
$origDbName="EmpDb"
$origDbLog="EmpDb_log"
$databaseName="EmpDb_Stage"
$databaseFile='C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\EmpDb_Stage\EmpDb_Stage.mdf'
$databaseLog='C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\EmpDb_Stage\EmpDb_Stage.ldf'
$standbyFile='C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\EmpDb_Stage\Standby'

$restoreDatabase = @"
USE master
GO
RESTORE DATABASE [Empdb_Stage] FROM DISK = N'$backupFile' WITH FILE = 1,
MOVE N'$origDbName' TO N'$databaseFile',
MOVE N'$origDbLog' TO N'$databaseLog',
STANDBY = N'$standbyFile', NOUNLOAD, STATS = 5
GO
"@

Invoke-Sqlcmd -ServerInstance $SqlInstance -Query $restoreDatabase
