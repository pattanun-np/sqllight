#ifndef PAGER_H
#define PAGER_H
#include <stdint.h>
const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 400
#define INVALID_PAGE_NUM UINT32_MAX
typedef struct
{
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void *pages[TABLE_MAX_PAGES];
} Pager;

void *get_page(Pager *pager, uint32_t page_num);
#endif