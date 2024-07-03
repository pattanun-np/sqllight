#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "repl.h"
#include "executor.h"

#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4096

void run_db_repl()
{
    InputBuffer* input_buffer = new_input_buffer();
    print_welcome_message();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_commnand(input_buffer))
            {
            case (META_COMMAND_SUCCESS):
                continue;

            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecognized command '%s'\n", input_buffer->buffer);
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
            continue;
        }

        excute_statement(&statement);
        printf("Executed.\n");
    }
}
