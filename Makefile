CC = gcc
CFLAGS = -Wall
TARGET = banker_algorithm
SRCS = banker_algorithm.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
