CC = gcc
CFLAGS = -Wall -Wextra
TARGET = play

all: $(TARGET)

$(TARGET): game.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

.PHONY: all clean