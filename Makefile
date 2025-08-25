TARGET = bin/*.o
SOURCE = src/main.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	gcc -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)