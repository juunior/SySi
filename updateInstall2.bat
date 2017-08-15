# Name: InstallWindowsUpdates.ps1
# Version: 1.0
# Comment: PowerShell script to install 
# Windows Update files
#
#########################################################

# Specify the location of the *.msu files
$updatedir = "C:\temp_dir\"
###

$files = Get-ChildItem $updatedir -Recurse
$msus = $files | ? {$_.extension -eq ".msu"}

foreach ($msu in $msus)
{
	write-host "Installing update $msu ..."
	$fullname = $msu.fullname
# Need to wrap in quotes as folder path may contain spaces
	$fullname = "`"" + $fullname + "`""
# Specify the command line parameters for wusa.exe
	$parameters = $fullname + " /quiet /norestart"
# Start wusa.exe and pass in the parameters
	$install = [System.Diagnostics.Process]::Start( "wusa",$parameters )
	$install.WaitForExit()
	write-host "Finished installing $msu"
}

write-host "Restarting Computer"
#Restart-Computer
