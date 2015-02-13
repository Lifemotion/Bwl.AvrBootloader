call testbox-compile.cmd
echo .
echo ..
echo ...
atprogram -t jtagice3 -i ISP -d atmega328P chiperase program -fl -fs -f testbox.elf
