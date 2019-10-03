xcopy "%~dp0..\Editor\resources" "%~dp0..\bin\Release-windows-x86_64\Editor\resources" /s /y /i /c
xcopy "%~dp0..\Caramel\deps\assimp\bin\Release\assimp-vc141-mt.dll" "%~dp0..\bin\Release-windows-x86_64\Editor\" /s /y /i /c
xcopy "%~dp0..\Editor\imgui.ini" "%~dp0..\bin\Release-windows-x86_64\Editor\" /s /y /i /c