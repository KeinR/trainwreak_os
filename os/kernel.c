
#include "tty.h"

void kmain() {
    // tty_putc(0xFF58, 0);
    // short *add = (short *)(0xb8000);
    // int F = add[0];
    // add[0] = 0xFF58;
    tty_init();
    tty_print(0x02, "Kernel booted into protected mode!");
    // tty_putc(0xFF58, 5);
    while(1);
}


