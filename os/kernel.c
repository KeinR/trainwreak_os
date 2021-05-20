
#include "tty.h"
#include "int.h"
#include "sysio.h"
#include "pic.h"
#include "keyboard.h"

extern void kern_test_interrupts();

void kmain() {
    pic_init();
    int_init();
    kb_init();
    pic_enable(1); // Keyboard
    tty_init();

    tty_print(0x02, "Kernel booted into protected mode!");

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


