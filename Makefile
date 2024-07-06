# Define the compiler
CC = gcc

# Define the flags for the compiler
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Define the target executables
TARGET_ORIG = build_orig/db
TEST_TARGET_ORIG = build_orig/test_db

TARGET_ASM = build_asm/db
TEST_TARGET_ASM = build_asm/test_db_asm

# Define the source files
SRC_ORIG = src/db.c 
SRC_ASM = src/db_asm.c 

TEST_SRC_ORIG = tests/test_db.c
TEST_SRC_ASM = tests/test_db_asm.c

# Define the object files
OBJS_ORIG = $(SRC_ORIG:src/%.c=build_orig/%.o)
OBJS_ASM = $(SRC_ASM:src/%.c=build_asm/%.o)

TEST_OBJS_ORIG = $(TEST_SRC_ORIG:tests/%.c=build_orig/%.o)
TEST_OBJS_ASM = $(TEST_SRC_ASM:tests/%.c=build_asm/%.o)

# Ensure build directories exist
.PHONY: prepare
prepare:
	mkdir -p build_orig
	mkdir -p build_asm

# Rule to build the original target executable
$(TARGET_ORIG): prepare $(OBJS_ORIG)
	$(CC) $(CFLAGS) -o $(TARGET_ORIG) $(OBJS_ORIG)

# Rule to build the ASM target executable
$(TARGET_ASM): prepare $(OBJS_ASM)
	$(CC) $(CFLAGS) -o $(TARGET_ASM) $(OBJS_ASM)

# Rule to build the original test executable
$(TEST_TARGET_ORIG): prepare $(TEST_OBJS_ORIG)
	$(CC) $(CFLAGS) -o $(TEST_TARGET_ORIG) $(TEST_OBJS_ORIG)

# Rule to build the ASM test executable
$(TEST_TARGET_ASM): prepare $(TEST_OBJS_ASM)
	$(CC) $(CFLAGS) -o $(TEST_TARGET_ASM) $(TEST_OBJS_ASM)

# Rule to build the object files from original source files
build_orig/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the object files from ASM source files
build_asm/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the test object files from original test files
build_orig/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the test object files from ASM test files
build_asm/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run the original target executable
.PHONY: run_orig
run_orig: $(TARGET_ORIG)
	./$(TARGET_ORIG) test.db

# Rule to run the ASM target executable
.PHONY: run_asm
run_asm: $(TARGET_ASM)
	./$(TARGET_ASM) test.db

# Rule to run the original test executable
.PHONY: test_orig
test_orig: $(TEST_TARGET_ORIG)
	./$(TEST_TARGET_ORIG)

# Rule to run the ASM test executable
.PHONY: test_asm
test_asm: $(TEST_TARGET_ASM)
	./$(TEST_TARGET_ASM)

# Clean rule to remove compiled files
.PHONY: clean
clean:
	rm -rf build_orig/* build_asm/*

# Rule to format source files
.PHONY: format
format:
	clang-format -style=Google -i src/*.c include/*.h
