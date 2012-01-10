CC=g++
CFLAGS=-Wall -g

testblock: testblock.cpp ../structure.cpp ../block.cpp
	$(CC) $(CFLAGS) -o $@ $^

testtetris: testtetris.cpp ../structure.cpp ../*block.cpp ../game.cpp ../rectangle.cpp
	$(CC) $(CFLAGS) -o $@ $^
