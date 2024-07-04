#ifndef STATMENT_H
#define STATMENT_H
#include "row.h"
typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct

{
    StatementType type;
    Row row_to_insert; // only used by insert statement
} Statement;

#endif