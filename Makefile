CFLAGS=-std=c++11 -g
maze: main.cpp Pathfinder.cpp Pathfinder.h PathfinderInterface.h
	g++ $(CFLAGS) -o Maze-Lab main.cpp Pathfinder.cpp