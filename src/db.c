#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "repl.h"

#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4096

Table* new_table() {
    Table* table = malloc(sizeof(Table));
    table->rows = malloc(sizeof(Row) * TABLE_MAX_PAGES);
    table->num_rows = 0;
    table->max_rows = TABLE_MAX_PAGES;
    return table;
}

void free_table(Table* table) {
    free(table->rows);
    free(table);
}

void serialize_row(Row* source, void* destination) {
    memcpy(destination, source, sizeof(Row));
}

void deserialize_row(void* source, Row* destination) {
    memcpy(destination, source, sizeof(Row));
}

void db_insert(Table* table, int id, const char* username, const char* email) {
    if (table->num_rows >= table->max_rows) {
        printf("Error: Table full.\n");
        return;
    }
    Row row;
    row.id = id;
    strncpy(row.username, username, sizeof(row.username) - 1);
    row.username[sizeof(row.username) - 1] = '\0';
    strncpy(row.email, email, sizeof(row.email) - 1);
    row.email[sizeof(row.email) - 1] = '\0';
    table->rows[table->num_rows] = row;
    table->num_rows++;
}

void db_select(Table* table) {
    for (size_t i = 0; i < table->num_rows; i++) {
        Row* row = &table->rows[i];
        printf("(%d, %s, %s)\n", row->id, row->username, row->email);
    }
}

void run_db_repl(Table* table) {
    InputBuffer* input_buffer = new_input_buffer();
    print_welcome_message();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strncmp(input_buffer->buffer, ".exit", 5) == 0) {
            close_input_buffer(input_buffer);
            free_table(table);
            exit(EXIT_SUCCESS);
        } else if (strncmp(input_buffer->buffer, ".help", 5) == 0) {
            print_help();
        } else if (strncmp(input_buffer->buffer, ".clear", 6) == 0) {
            clear_screen();
        } else if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
            int id;
            char username[32];
            char email[255];
            int args_assigned = sscanf(input_buffer->buffer, "insert %d %31s %254s", &id, username, email);
            if (args_assigned < 3) {
                printf("Error: Syntax error. Could not parse statement.\n");
                continue;
            }
            db_insert(table, id, username, email);
        } else if (strncmp(input_buffer->buffer, "select", 6) == 0) {
            db_select(table);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}
