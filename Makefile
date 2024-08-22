# Define the compiler
CC = gcc

# Define the compiler flags
CFLAGS = -Wall -Wextra -std=c99

# List all the source files
SRCS = edito.c terminal.c input.c output.c abuf.c fileio.c rowops.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the target executable
TARGET = edito

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)