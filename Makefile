CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
LDLIBS = -lncurses

SRCS = main.c game.c bullets.c pantalla.c enemigo.c
OBJS = $(SRCS:.c=.o)

TARGET = game

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean


