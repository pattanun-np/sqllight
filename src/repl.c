#include "repl.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InputBuffer *new_input_buffer() {
  InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;
  return input_buffer;
}

void print_prompt() { printf("sqllight > "); }

void read_input(InputBuffer *input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

void print_help() {
  printf("Available commands:\n");
  printf(".exit - Exit the REPL\n");
  printf(".help - Show this help message\n");
  printf(".clear - Clear the screen\n");
}

// clear the screen
void clear_screen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

MetaCommandResult do_meta_commnand(InputBuffer *input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit")) {
    exit(EXIT_SUCCESS);
  } else if (strcmp(input_buffer->buffer, ".help")) {
    print_help();
    return META_COMMAND_SUCCESS;
  } else if (strcmp(input_buffer->buffer, ".clear")) {
    clear_screen();
    return META_COMMAND_SUCCESS;
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

// Prepare the statement
PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  } else if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  else if (strncmp(input_buffer->buffer, "update", 6) == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  else if (strcmp(input_buffer->buffer, "delete") == 0) {
    statement->type = STATEMENT_DELETE;
    return PREPARE_SUCCESS;
  } else {
    statement->type = STATEMENT_UNRECOGNIZED;
    return PREPARE_UNRECOGNIZED_STATEMENT;
  }
}

void print_welcome_message() {
  printf("***************************\n");
  printf("* Welcome to SQL Light Database! *\n");
  printf("* Version 0.1.0\n");
  printf("* Type .help for commands *\n");
  printf("***************************\n\n");
}
