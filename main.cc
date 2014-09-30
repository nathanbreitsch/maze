#include "maze.h"
#include "mazeDrawer.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#endif
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;
using std::cin;
using std::pair;


MazeDrawer drawer;
Maze * maze;
pair<int, int> start;
pair<int, int> finish;
pair<int, int> current;

extern "C" void trampoline(){
        drawer.draw(*maze);
}

extern "C" void idle(){
    while(current != finish){
        current = maze->step();
        //time delay
        usleep(10000);
        drawer.draw(*maze);
    }
    
}

int main(int argc, char* argv[]){
    int numRows, numCols;
    cout << "Enter number of rows." << endl;
    cin >> numRows;
    cout << "Enter number of columns." << endl;
    cin >> numCols;
    cout << "Enter coordinate of start: x y (separated by space)" << endl;
    cin >> start.first >> start.second;
    cout << "Enter coordinate of finish: x y (separated by space)" << endl;
    cin >> finish.first >> finish.second;
    current = start;
    maze = new Maze(numRows, numCols, start, finish);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  
    glutInitWindowPosition(200,200);
    glutInitWindowSize(512,512);
    glutCreateWindow("maze");
    glutDisplayFunc(trampoline);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
   
}

