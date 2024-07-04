# Define the compiler
CC = gcc

# Define the flags for the compiler
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Define the target executables
TARGET = build/db
TEST_TARGET = build/test_repl

# Define the source files
src = src/db.c

TEST_src = tests/test_repl.c

# Define the object files
OBJS = $(src:src/%.c=build/%.o)
TEST_OBJS = $(TEST_src:src/%.c=build/%.o)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build the object files
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the test object files
build/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the target executable
run: $(TARGET)
	./$(TARGET) mydb.db

# Rule to run the test executable
test: $(TEST_TARGET)
	./$(TEST_TARGET)
	
.PHONY: build
build:
	 mkdir ./build

# Clean rule to remove compiled files
.PHONY: clean
clean:
	rm -f build/*

# Rule to format source files
.PHONY: format
format:
	clang-format -style=Google -i src/*.c include/*.h
