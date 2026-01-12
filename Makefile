CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/bmp_utils.c
OBJ = $(SRC:.c=.o)
TARGET = bmp-processor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
