call paths.cmd
atprogram -t atmelice -i JTAG -d atmega2560 chiperase program -fl -fs -f boot_m2560.elf
atprogram -t atmelice -i ISP -d atmega2560 chiperase program -fl -fs -f boot_m2560.elf