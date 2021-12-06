$BackupDir = "C:\Backups\"

$SqlStagePath = "C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\"

function DisplayMenu {
	cls
	Write-Host "~~~~~~~~~~~~~~~~~~ Menu Title ~~~~~~~~~~~~~~~~~~" -ForegroundColor Cyan
	Write-Host "  D: Restoring Database "
	Write-Host "  L: Restoring Transaction Logs "
	Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
}

function RestoreDb {
    cls

	Write-Host "  Restore Database "  -ForegroundColor Cyan
	Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta

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
RESTORE DATABASE [$databaseName] FROM DISK = N'$backupFile' WITH FILE = 1,
MOVE N'$origDbName' TO N'$databaseFile',
MOVE N'$origDbLog' TO N'$databaseLog',
STANDBY = N'$standbyFile', NOUNLOAD, STATS = 5
GO
"@

    Invoke-Sqlcmd -ServerInstance $SqlInstance -Query $restoreDatabase
}

function RestoreLog {
    cls
	Write-Host "  Restore Log " -ForegroundColor Cyan
	Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
  
    $SqlInstance="WIN2016TARGETA"
    $trnFile="C:\Backups\Empdb.trn"
    $databaseName="EmpDb_Stage"
    $standby2File='C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\EmpDb_Stage\Standby2'

$restoreDatabase = @"
USE master
GO
RESTORE LOG [$databaseName] FROM DISK = N'$trnFile' WITH 
STANDBY = N'$standby2File', NOUNLOAD, STATS = 10
GO
"@

    Invoke-Sqlcmd -ServerInstance $SqlInstance -Query $restoreDatabase
}

$DbName = Read-Host "Enter the name of the SQL Server staging database:"
write-output "Staging server name = $DbName"

DisplayMenu
$answer = (Read-Host "Please make a selection").ToUpper()

while ($answer -ne 'Q') {
    switch ($answer)
    {
        'Q' { exit }
        'D' { RestoreDb }
        'L' { RestoreLog }
        Default { Write-Output "Error!! " }
    }
    Write-Host " "
	Read-Host -Prompt "Press any key to continue or CTRL+C to quit" 
	DisplayMenu
    $answer = (Read-Host "Please make a selection").ToUpper()
}


