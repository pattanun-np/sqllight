#ifndef REPL_H
#define REPL_H

#include <stddef.h>

#ifdef _WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#include <sys/types.h>
#endif

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef struct {
    int id;
    char username[32];
    char email[255];
} Row;

typedef struct {
    Row* rows;
    size_t num_rows;
    size_t max_rows;
} Table;

InputBuffer* new_input_buffer();
void print_prompt();
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);
void print_help();
void clear_screen();
void run_repl();
void run_db_repl(Table* table);
Table* new_table();
void free_table(Table* table);

#endif
