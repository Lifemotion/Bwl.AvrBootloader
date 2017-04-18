call orlan-sensors.cmd
atprogram -t atmelice -i JTAG -d atmega2560 chiperase program -fl -fs -f orlan-sensors-boot.elf

pause