CC := g++
CFLAGS := -Wall

OBJS := main.o Snake.o Game.o
SFLIB := -LExternal/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDES := -IExternal/SFML/include
SRC := SnakeGame
ICO := $(SRC)/snakeicon.res
OUTPUT := $(SRC)/output/$(SRC).exe

all: Compile clean

Compile: $(OBJS)
	$(CC) $(CFLAGS) $^ $(SFLIB) -mwindows $(ICO) -o $(OUTPUT)

Game.o: $(SRC)/Game.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Snake.o: $(SRC)/Snake.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<


clean:
	del *.o