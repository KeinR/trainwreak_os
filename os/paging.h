#ifndef SYS_PAGING_H_
#define SYS_PAGING_H_

#include <stdint.h>

#define PAGE_ERROR -1

uint32_t page_alloc();
void page_free(uint32_t page);

#endif




