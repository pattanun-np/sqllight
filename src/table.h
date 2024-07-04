#ifndef TABLE_H
#define TABLE_H
#include "pager.h"
#include <stdint.h>

typedef struct
{
    Pager *pager;
    uint32_t root_page_num;
} Table;

#endif