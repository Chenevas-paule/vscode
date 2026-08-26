CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

TARGET = projet
OBJ = main.o peripherique.o

.PHONY: all clean valgrind

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) < commandes_test.txt

clean:
	rm -f $(OBJ) $(TARGET)