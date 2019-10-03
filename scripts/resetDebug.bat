xcopy "%~dp0..\Editor\resources" "%~dp0..\bin\Debug-windows-x86_64\Editor\resources" /s /y /i /c
xcopy "%~dp0..\Editor\imgui.ini" "%~dp0..\bin\Debug-windows-x86_64\Editor" /s /y /i /c
xcopy "%~dp0..\Editor\imgui.ini" "%~dp0" /s /y /i /c

call "%~dp0..\bin\Debug-windows-x86_64\Editor\Editor.exe