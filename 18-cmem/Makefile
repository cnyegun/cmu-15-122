# Compiler
CC = gcc

# Compiler flags:
#  -Wall: all common warnings
#  -Wextra: extra good warnings
#  -Wpedantic: strict ISO C
#  -Werror: turn warnings into errors
#  -g: add debug info
#  -O0: (optional) disable optimizations for debugging
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g -O0

# Sources and objects
SRCS = test.c uba.c
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = test

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c into .o
%.o: %.c uba.h
	$(CC) $(CFLAGS) -c $< -o $@

# Remove build products
clean:
	rm -f $(OBJS) $(TARGET)

# Remove everything including editor backups
distclean: clean
	rm -f *~ *.bak

.PHONY: all clean distclean

