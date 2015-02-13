call paths.cmd
echo off
cls
copy testbox.elf testbox.elf.bak
del *.elf /q
cd ..
cd Bwl.AvrBootLoader
cd CFG_TESTPLATFORM_ONE
..\guidgen #define DEV_GUID
del *.elf /q
make clean
make all
copy Bwl.AvrBootLoader.elf ..\..\autobuild\testbox.elf
cd ..\..
cd autobuild

cat ..\guid
echo .
echo .
echo ..
echo ...
atprogram -t jtagice3 -i ISP -d atmega328P chiperase program -fl -fs -f testbox.elf
