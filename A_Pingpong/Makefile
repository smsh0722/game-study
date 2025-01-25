# Compiler and Flags
CC = g++
CFLAGS = -Wall -I ../External/SDL2/include -D_REENTRANT
LDFLAGS = -L ../External/SDL2/lib -lmingw32 -lSDL2main -lSDL2 -mwindows
SRCS = Main.cpp Game.cpp 
OBJS = $(SRCS:.cpp=.o)
EXEC = pingpong

# Build Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /q $(OBJS) $(EXEC)
