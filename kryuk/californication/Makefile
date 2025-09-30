CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_GNU_SOURCE
TARGETS = californication
SOURCE = californication.c

all: $(TARGETS)

$(TARGETS): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGETS) $(SOURCE)

.PHONY: all
