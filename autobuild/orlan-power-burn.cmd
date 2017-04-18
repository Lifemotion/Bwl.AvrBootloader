call orlan-power.cmd
atprogram -t atmelice -i JTAG -d atmega324PA chiperase program -fl -fs -f orlan-power-boot.elf

pause