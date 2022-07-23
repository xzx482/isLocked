cd %~dp0
cl -c isLocked.cpp
link -DLL -out:isLocked.dll isLocked.obj
pause