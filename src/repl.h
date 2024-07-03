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

// Meta commands
typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// statement types
typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_DELETE,
    STATEMENT_UPDATE,
    STATEMENT_UNRECOGNIZED
} StatementType;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef struct
{
    StatementType type;
} Statement;

InputBuffer* new_input_buffer();

void print_prompt();
void print_welcome_message();
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);
void print_help();
void clear_screen();

MetaCommandResult do_meta_commnand(InputBuffer *input_buffer);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

#endif
