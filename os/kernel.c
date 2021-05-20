
#include "tty.h"
#include "int.h"
#include "sysio.h"

extern void kern_test_interrupts();

void kmain() {
    tty_init();
    tty_print(0x02, "Kernel booted into protected mode!");
    int_init();
    // kern_test_interrupts();
    while(1) {
        /*
        outb(0xf0);
        iowait();
        char code;
        code = inb()
        if (code != 0xfa) continue;
        char 

        int faf = code / 2;
        */
    }
}


