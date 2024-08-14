# Makefile for MiniFlow project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I. -Wall

# Source files
SRCS = minitensor.c

# Output executable
TARGET = miniflow

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up build files
clean:
	rm -f $(TARGET)