@echo off
cd /d "c:\temp_dir\"
for /f "delims=" %%f in ('dir /s /b *.inf ') do rundll32 syssetup,SetupInfObjectInstallAction DefaultInstall 128 "%%f"
