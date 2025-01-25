CC = g++
CFLAGS = -I ../External/SDL/include
LDFLAGS = -L ../External/SDL/lib -lSDL2
TARGET = Main
SRC = Main.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
