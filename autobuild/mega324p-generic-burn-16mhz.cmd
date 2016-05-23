call paths.cmd
atprogram -t atmelice -i JTAG -d atmega324P chiperase program -fl -fs -f boot_m324p_16mhz.elf
atprogram -t atmelice -i JTAG -d atmega324PA chiperase program -fl -fs -f boot_m324p_16mhz.elf
