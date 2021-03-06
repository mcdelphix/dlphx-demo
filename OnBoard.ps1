$BackupDir = "C:\Backups\"
$SqlStagePath = "C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\"

function DisplayMenu {
	cls
	Write-Host "~~~~~~~~~~~~~~~~~~ Menu Title ~~~~~~~~~~~~~~~~~~" -ForegroundColor Cyan
	Write-Host "  D: Restoring Database "
	Write-Host "  L: Restoring Transaction Logs "
	Write-Host "  V: View Delphix Logs "
    Write-Host "  Q: Quit "
	Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
}

function ViewLogs {
    param (
        [Parameter()] [string] $DbName
        )

    cls

    Write-Host "  View Delphix Logs for $DbName "  -ForegroundColor Cyan
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
    $databaseName=$DbName+"_Stage"
    $logFile="C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\logs\"+$databaseName+"\debug.log"

    Write-Host "$logFile"
    $wait2 = Read-Host "Press any key to begin viewing the above log. "
    gc $logFile -wait
}

function RestoreDb {
    param (
        [Parameter()] [string] $DbName
        )

    cls

	Write-Host "  Restore Database $DbName "  -ForegroundColor Cyan
	Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta

    $SqlInstance="WIN2016TARGETA"
    $backupFile="C:\Backups\"+$DbName+".bak"
    $origDbName=$DbName
    $origDbLog=$DbName+"_log"
    $databaseName=$DbName+"_Stage"
    $databaseFile="C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\"+$databaseName+"\$databaseName.mdf"
    $databaseLog="C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\"+$databaseName+"\$databaseName.ldf"
    $standbyFile="C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\"+$databaseName+"\Standby"

    $restoreDatabase = @"
USE master
GO
RESTORE DATABASE [$databaseName] FROM DISK = N'$backupFile' WITH FILE = 1,
MOVE N'$origDbName' TO N'$databaseFile',
MOVE N'$origDbLog' TO N'$databaseLog',
STANDBY = N'$standbyFile', NOUNLOAD, STATS = 5
GO
"@

    Write-Host "$restoreDatabase"
    $wait2 = Read-Host "Press any key to begin restoring the $DbName database. "

    Invoke-Sqlcmd -ServerInstance $SqlInstance -Query $restoreDatabase
}

function RestoreLog {
    param (
[Parameter()] [string] $DbName
)

    cls
    Write-Host "  Restore Log for database $DbName " -ForegroundColor Cyan
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" -ForegroundColor Magenta
  
    $SqlInstance="WIN2016TARGETA"
    $trnFile="C:\Backups\"+$DbName+".trn"
    $databaseName=$DbName+"_Stage"
    $standby2File="C:\Program Files\Delphix\DelphixConnector\Sqlserver Manual Discovery\mnt\"+$DbName+"_Stage\Standby2"

$restoreDatabase = @"
USE master
GO
RESTORE LOG [$databaseName] FROM DISK = N'$trnFile' WITH 
STANDBY = N'$standby2File', NOUNLOAD, STATS = 10
GO
"@

    Write-Host "$restoreDatabase"
    $wait2 = Read-Host "Press any key to begin restoring the SQL TLOGs. "

    Invoke-Sqlcmd -ServerInstance $SqlInstance -Query $restoreDatabase
}

$DbName = Read-Host "Enter the name of the SQL database (EmpDb): "

DisplayMenu
$answer = (Read-Host "Please make a selection (Q, D, L) ").ToUpper()

while ($answer -ne 'Q') {
    switch ($answer)
    {
        'Q' { exit }
        'D' { RestoreDb $DbName }
        'L' { RestoreLog $DbName }
        'V' { ViewLogs $DbName }
        Default { Write-Output "Invalid selection !! " }
    }
    Write-Host " "
    ## Read-Host -Prompt "Press any key to continue or CTRL+C to quit" 
    DisplayMenu
    $answer = (Read-Host "Please make a selection (Q, D, L, V) ").ToUpper()
}


