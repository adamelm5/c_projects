CC = gcc
CFLAGS = -Wall -Wextra
TARGET = mines

all: $(TARGET)

$(TARGET): mines.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

.PHONY: all clean