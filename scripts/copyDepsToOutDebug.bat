xcopy "%~dp0..\Editor\resources" "%~dp0..\bin\Debug-windows-x86_64\Editor\resources" /s /y /i /c
xcopy "%~dp0..\Caramel\deps\assimp\bin\Debug\assimp-vc141-mtd.dll" "%~dp0..\bin\Debug-windows-x86_64\Editor\" /s /y /i /c
xcopy "%~dp0..\Editor\imgui.ini" "%~dp0..\bin\Debug-windows-x86_64\Editor\" /s /y /i /c
pause