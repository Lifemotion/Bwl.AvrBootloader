set CFG_NAME=CFG_ORLAN_TIMESYNC
set FILENAME=boot_timesync

call paths.cmd
echo off
cls
copy %FILENAME%.elf %FILENAME%.elf.bak
del %FILENAME%.elf /q
del *.elf /q
cd ..
cd Bwl.SimplSerial.AvrBootLoader
cd %CFG_NAME%
if ERRORLEVEL 1 goto fail
..\guidgen #define DEV_GUID
del *.elf /q
make clean
make all
if ERRORLEVEL 1 goto fail
copy Bwl.SimplSerial.AvrBootLoader.elf ..\..\autobuild\%FILENAME%.elf
cat ..\..\guid
echo.
echo.
echo ### Compile OK! ###
goto end

:fail
echo.
echo ### Error! Try to build with Atmel Studio 7.0 First ###
goto end

:end
cd ..\..
cd autobuild


atprogram -t atmelice -i JTAG -d atmega324pa chiperase program -fl -fs -f boot_timesync.elf
pause