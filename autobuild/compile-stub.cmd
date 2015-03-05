call paths.cmd
echo off
cls
copy %FILENAME%.elf %FILENAME%.elf.bak
del *.elf /q
cd ..
cd Bwl.AvrBootLoader
cd %CFG_NAME%
if ERRORLEVEL 1 goto fail
..\guidgen #define DEV_GUID
del *.elf /q
make clean
make all
if ERRORLEVEL 1 goto fail
copy Bwl.AvrBootLoader.elf ..\..\autobuild\%FILENAME%.elf
cat ..\..\guid
echo.
echo.
echo ### Compile OK! ###
goto end

:fail
echo.
echo ### Error! Try to build with Atmel Studio 6.2 First ###
goto end

:end
cd ..\..
cd autobuild