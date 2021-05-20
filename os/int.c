#include <stdint.h>

#include "int.h"
#include "sysio.h"
#include "pic.h"
#include "kernel.h"

struct idtEntry {
    uint16_t ofsLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t ofsHigh;
} __attribute__((packed));

interrupt_t intHandleTab[256];
struct idtEntry idt[256];

static void int_setIDT(int index, void *address, uint16_t type, uint16_t selector);
static void int_setKernelIDT(int index, void *address);
void int_handler(); // Ref int.asm

// int.asm
extern void int_handler_32();
extern void int_handler_33();
extern void int_handler_34();
extern void int_handler_35();
extern void int_handler_36();
extern void int_handler_37();
extern void int_handler_38();
extern void int_handler_39();
extern void int_handler_40();
extern void int_handler_41();
extern void int_handler_42();
extern void int_handler_43();
extern void int_handler_44();
extern void int_handler_45();
extern void int_handler_46();
extern void int_handler_47();
extern void int_handler_48();
extern void int_loadIDT(void *ptr);

void int_setIDT(int index, void *address, uint16_t type, uint16_t selector) {
    unsigned long addr = (unsigned long)address;
    idt[index].ofsLow = addr & 0xFFFF;
    idt[index].ofsHigh = (addr >> 16) & 0xFFFF; // The AND is probobly uncesessary if the address really is 32 bits
    idt[index].type = type;
    idt[index].selector = selector;
    idt[index].zero = 0;
}
void int_setKernelIDT(int index, void *address) {
    int_setIDT(index, address, 0x8E, KERNEL_CODE_SEGMENT);
}

void int_init() {
    for (int i = 0; i < 256; i++) intHandleTab[i] = 0;
    // TEMP
    for (int i = 0; i < 256; i++) {
        int_setKernelIDT(i, int_handler_48);
    }

    int_setKernelIDT(32, int_handler_32);
    int_setKernelIDT(33, int_handler_33);
    int_setKernelIDT(34, int_handler_34);
    int_setKernelIDT(35, int_handler_35);
    int_setKernelIDT(36, int_handler_36);
    int_setKernelIDT(37, int_handler_37);
    int_setKernelIDT(38, int_handler_38);
    int_setKernelIDT(39, int_handler_39);
    int_setKernelIDT(40, int_handler_40);
    int_setKernelIDT(41, int_handler_41);
    int_setKernelIDT(42, int_handler_42);
    int_setKernelIDT(43, int_handler_43);
    int_setKernelIDT(44, int_handler_44);
    int_setKernelIDT(45, int_handler_45);
    int_setKernelIDT(46, int_handler_46);
    int_setKernelIDT(47, int_handler_47);

    struct idt_register {
        uint16_t limit;
        uint16_t base_lo;
        uint16_t base_hi;
    } __attribute__((packed));

    unsigned long idtAddr = (unsigned long)&idt;
    struct idt_register ireg;
    ireg.limit = sizeof(struct idtEntry) * 256 - 1;
    ireg.base_lo = idtAddr & 0xffff;
    ireg.base_hi = (idtAddr >> 16) & 0xffff; // The AND is probobly uncesessary

    int_loadIDT(&ireg);
}

void int_handler(int interrupt, int error) {
    interrupt_t func = intHandleTab[interrupt];
    if (func != 0) {
        func(interrupt, error);
    }
    pic_sendEOI(interrupt);
}

void int_setHandle(int interrupt, interrupt_t handle) {
    intHandleTab[interrupt] = handle;
}


