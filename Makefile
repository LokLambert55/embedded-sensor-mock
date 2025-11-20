CC=gcc
CFLAGS=-Wall -Wextra -std=c11

TARGET=embedded_sensor_mock
SRC=src/main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)