#include "repl.h"
#include "executor.h"
#include <stdio.h>

void excute_statement(Statement *statement)
{
    switch (statement->type)
    {
    case (STATEMENT_INSERT):
        printf("This is where insert statement \n");
        break;

    case (STATEMENT_SELECT):
        printf("This is where select \n");
        break;

    case (STATEMENT_DELETE):
        printf("This is where delete statement \n");
        break;

    case (STATEMENT_UPDATE):
        printf("This us where update statement \n");
        break;
    case (STATEMENT_UNRECOGNIZED):
        printf("This is where unrecognized statement \n");
        break;
    }
}