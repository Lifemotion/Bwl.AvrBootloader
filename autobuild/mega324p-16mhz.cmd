call mega324p-generic-compile-16mhz.cmd
atprogram -t atmelice -i JTAG -d atmega324P chiperase program -fl -fs -f boot_m324p_16mhz.elf
pause
