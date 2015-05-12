@SET mypath=%~dp0
@SET SCRIPT_DIR=%mypath:~0,-1%
@SET PROJECT_DIR=%SCRIPT_DIR%\..

@set year=%date:~6,4%
@set month=%date:~3,2%
@set day=%date:~0,2%

@set hours=%time:~0,2%
@set mins=%time:~3,2%

@set filename=D:\Dropbox\PoniesProjects\Ponies_(%year%.%month%.%day%)_(%hours%-%mins%).zip
@echo %filename%
@dir %PROJECT_DIR%
@pause
#@c:\"Program Files"\7-Zip\7z.exe A -tzip -r -x@exclusions.txt -mx0 -ssw "%filename%" %PROJECT_DIR%\Project %PROJECT_DIR%\scripts %PROJECT_DIR%\Documents %PROJECT_DIR%\Art
@c:\"Program Files"\7-Zip\7z.exe A -tzip -r -x@exclusions.txt -mx0 -ssw "%filename%" %PROJECT_DIR%\*
@pause