#ifndef MAZE_DRAWER_H
#define MAZE_DRAWER_H

#include "maze.h"
using std::pair;

class MazeDrawer{
public:
    //draws maze
    void draw(Maze const & maze);
    
private:
    const float WIDTH = 2.0;
    const float HEIGHT = 2.0;
    const float MARGIN = 0.1;
    float gridWidth_;
    float gridHeight_;
    void translate_x(float & x);
    void translate_y(float & y);
    void drawArrow(pair<int,int> lastStep, pair<int,int> nextStep);
    void drawMarker(int i,int j);//
    void drawTop(int i, int j); //draws top of cell i,j
    void drawLeft(int i, int j); //draws left of cell i,j
    void drawRight(int i, int j);//draws right of cell i,j
    void drawBottom(int i, int j);//draws bottom of cell i,j
};

#endif