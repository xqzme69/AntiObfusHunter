@echo off
setlocal
call "C:\Program Files\Microsoft Visual Studio\18\Professional\VC\Auxiliary\Build\vcvars64.bat"

echo [1] Mutating obfus.h...
python mutate_obfus.py obfus_original.h obfus_mutated.h
if %errorlevel% neq 0 exit /b %errorlevel%

echo [2] Compiling main.cpp...
cl /nologo /EHsc /std:c++20 /O2 main.cpp
if %errorlevel% neq 0 exit /b %errorlevel%

echo [3] Build complete! Run main.exe
endlocal
