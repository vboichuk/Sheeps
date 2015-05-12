@SET mypath=%~dp0
@SET CURRENT_DIR=%mypath:~0,-1%
@SET RESOURCES_DIR=%CURRENT_DIR%\..\Project\Resources\assets
@SET ASSETS_DIR=%CURRENT_DIR%\..\Project\proj.android\assets

rd %ASSETS_DIR% /s /q 
mkdir %ASSETS_DIR%

xcopy %RESOURCES_DIR% %ASSETS_DIR% /E

