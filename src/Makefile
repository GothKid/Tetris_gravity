CC=g++
CFLAGS=-Wall -g -I/Library/Frameworks/SDL.framework/Headers
FRAMEWORKS=-framework SDL -framework Cocoa -framework SDL_image -framework SDL_ttf

all: ../bin tetris

tetris: L_block.o block.o box_block.o game.o line_block.o rectangle.o reverse_l_block.o reverse_s_block.o s_block.o structure.o t_block.o tetris.o *.m
	$(CC) $(CFLAGS) $(FRAMEWORKS) -o ../bin/$@ $^
L_block.o: L_block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
block.o: block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
box_block.o: box_block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
game.o: game.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
line_block.o: line_block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
rectangle.o: rectangle.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
reverse_l_block.o: reverse_l_block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
reverse_s_block.o: reverse_s_block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
s_block.o: s_block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
structure.o: structure.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
t_block.o: t_block.cpp
	$(CC) $(CFLAGS) -c -o $@ $^
tetris.o: tetris.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

../bin:
	mkdir ../bin
clean:
	rm -f *.o ../bin/tetris
