#include "paging.h"

#include <stdbool.h>

#define AP_SIZE (0x100000000 / 0x1000 / 32)

// Maps all 4KB pages
// Max mem / page size / int size
// TODO: Use bitmap instead
uint8_t allocPages[AP_SIZE];

static void page_writeAlloc(int i, int count);
extern void page_owned();

void page_init() {
    for (int i = 0; i < AP_SIZE; i++) allocPages[i] = 0;
}

void page_writeAlloc(uint32_t i, int count) {
    for (; i < i + count; i++) {
        allocPages[i] = 1;
    }
}

uint32_t page_alloc(int count) {
    int lo = 0;
    uint32_t i = 0;
    bool seek = true;
    for (; i < AP_SIZE && i - lo < count; i++) {
        uint32_t v = allocPages[i];
        if (v == 0) {
            seek = false;
        } else if (!seek) {
            lo = i;
            seek = true;
        }
    }
    if (i - lo >= count) {
        page_writeAlloc(i, count);
        return i;
    }
    return PAGE_ERROR;
}

void page_free(uint32_t page) {
    allocPages[page] = 0;
}


