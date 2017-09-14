call orlan-power-v3.cmd
atprogram -t atmelice -i JTAG -d atmega2560 chiperase program -fl -fs -f orlan-power-v3-boot.elf

pause