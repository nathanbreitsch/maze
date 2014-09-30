all: maze

maze: main.o maze.o mazeDrawer.o 
	g++ -framework OpenGL -framework GLUT -o maze main.o maze.o mazeDrawer.o -std=c++11

main.o: main.cc
	g++ -c main.cc

maze.o: maze.cc
	g++ -c maze.cc

mazeDrawer.o: mazeDrawer.cc
	g++ -c mazeDrawer.cc

