CC = gcc
CFLAGS = -Wall -g3
LN = -lSDL2 -lSDL2_image -lSDL2_ttf
OBJMODULES = build/event.o build/view.o build/drawing.o build/savemap.o build/genmap.o build/simplex-noise.o build/map.o build/mathtools.o build/game.o

build/%.o: lib/%.c include/%.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LN)

game: main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o build/$@ $(LN)

clean:
	rm build/*.o

run: 
	build/game