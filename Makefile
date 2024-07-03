# Define the compiler
CC = gcc

# Define the flags for the compiler
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Define the target executables
TARGET = build/db
TEST_TARGET = build/test_repl

# Define the source files
SRCS = src/db.c src/repl.c src/main.c
TEST_SRCS = tests/test_repl.c src/repl.c

# Define the object files
OBJS = $(SRCS:src/%.c=build/%.o)
TEST_OBJS = $(TEST_SRCS:%.c=build/%.o)

# Ensure build directory exists
DIRS = build

$(DIRS):
	mkdir -p $(DIRS)

# Rule to build the target executable
$(TARGET): $(DIRS) $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the test executable
$(TEST_TARGET): $(DIRS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build the object files
build/%.o: src/%.c | $(DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the test object files
build/%.o: tests/%.c | $(DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the target executable
run: $(TARGET)
	./$(TARGET) mydb.db

# Rule to run the test executable
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean rule to remove compiled files
.PHONY: clean
clean:
	rm -f build/*

# Rule to format source files
.PHONY: format
format:
	clang-format -style=Google -i src/*.c include/*.h
