call trafficlight-compile.cmd
echo .
echo ..
echo ...
atprogram -t jtagice3 -i ISP -d atmega168PA chiperase program -fl -fs -f boot_trafficlight.elf
