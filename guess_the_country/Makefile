CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCS = src/devine.c src/fichiers.c src/manip.c

OBJS = $(SRCS:.c=.o)
TARGET = play

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

reinstall: clean all

.PHONY: all clean reinstall