call orlan-timesync.cmd
atprogram -t atmelice -i JTAG -d atmega324PA chiperase program -fl -fs -f orlan-timesync-boot.elf

pause