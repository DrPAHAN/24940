CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_GNU_SOURCE
TARGET = getopt_program
SOURCE = getopt.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

.PHONY: all
