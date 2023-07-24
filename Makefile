# Makefile for Mode Switcher GTK application

# Compiler
CC = gcc

# Compiler flags
CFLAGS = `pkg-config --cflags gtk+-3.0`

# Linker flags
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Source files
SRC = mode_switcher.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
EXECUTABLE = themeswitcher

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)
