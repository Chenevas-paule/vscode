CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

TARGET = projet

.PHONY: all clean valgrind

all: $(TARGET)

$(TARGET): main.c peripherique.c peripherique.h
	$(CC) $(CFLAGS) main.c peripherique.c -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) < commandes_test.txt

clean:
	rm -f $(TARGET)