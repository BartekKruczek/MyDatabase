TARGET = bin/main
BIN_DIR = bin
SOURCES = src/main.c src/file.c src/parse.c
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
ARGS = -n -f ./mydb.db -a "Jan Kowalski;Warszawa;10"

all: $(TARGET)

$(TARGET): $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)