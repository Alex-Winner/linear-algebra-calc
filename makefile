# Compiler and compiler flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic-errors -Werror 

# Name of the executable
TARGET = mainmat

# Build the executable
$(TARGET): mainmat.o mymat.o
	$(CC) $(CFLAGS) mainmat.o mymat.o -o $(TARGET) 

# Compile mainmat.c
mainmat.o: mainmat.c mainmat.h
	$(CC) $(CFLAGS) -c mainmat.c

# Compile mymat.c
mymat.o: mymat.c mymat.h
	$(CC) $(CFLAGS) -c mymat.c

# Remove all object files
clean:
	rm -f *.o