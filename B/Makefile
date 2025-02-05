# Compiler and Flags
CC = g++
CFLAGS = -Wall -Wextra -I"../External/SDL2/include" -D_REENTRANT
LDFLAGS = -L"../External/SDL2/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows
SRCS = Main.cpp Game.cpp Actor.cpp Ship.cpp Component.cpp SpriteComponent.cpp AnimSpriteComponent.cpp BGSpriteComponent.cpp Math.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = B

# Build Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /q $(OBJS) $(EXEC)
