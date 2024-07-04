#ifndef CURSOR_H
#define CURSOR_H
#include <stdint.h>
#include <stdbool.h>
#include "table.h"

typedef struct
{
    Table *table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table; // Indicates a position one past the last element
} Cursor;

#endif