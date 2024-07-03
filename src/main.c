#include <stdio.h>
#include <stdlib.h>
#include "repl.h"
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Initialize your database here, for example, by loading from a file.
    // For now, we'll assume the table is created in memory.
    Table *table = new_table();

    // Run the REPL
    run_db_repl(table);

    // Free the table when done (though run_db_repl will handle this on exit)
    free_table(table);

    return 0;
}
