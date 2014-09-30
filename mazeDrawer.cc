#include "mazeDrawer.h"
#include <GLUT/glut.h>
#include <iostream>
using std::pair;
using std::cout;
using std::endl;

void MazeDrawer::translate_y(float & x){
    x = x - (WIDTH - MARGIN) / 2.0;
}

void MazeDrawer::translate_x(float & y){
    y = y - (HEIGHT - MARGIN) / 2.0;
}

void MazeDrawer::drawTop(int i, int j){
    float x1 = j*gridWidth_;
    float x2 = (j+1)*gridWidth_;
    float y = (i)*gridHeight_;
    translate_x(x1);
    translate_x(x2);
    translate_y(y);
    glVertex2f(x1, y);
    glVertex2f(x2, y);
}

void MazeDrawer::drawLeft(int i, int j){
    float y1 = i*gridHeight_;
    float y2 = (i+1)*gridHeight_;
    float x = j*gridWidth_;
    translate_y(y1);
    translate_y(y2);
    translate_x(x);
    glVertex2f(x, y1);
    glVertex2f(x, y2);
}

void MazeDrawer::drawRight(int i, int j){
    float y1 = i*gridHeight_;
    float y2 = (i+1)*gridHeight_;
    float x = (j+1)*gridWidth_;
    translate_y(y1);
    translate_y(y2);
    translate_x(x);
    glVertex2f(x, y1);
    glVertex2f(x, y2);
}

void MazeDrawer::drawBottom(int i, int j){
    float x1 = j*gridWidth_;
    float x2 = (j+1)*gridWidth_;
    float y = (i + 1)*gridHeight_;
    translate_x(x1);
    translate_x(x2);
    translate_y(y);
    glVertex2f(x1, y);
    glVertex2f(x2, y);
}

void MazeDrawer::drawMarker(int i,int j){
    float x_start = (j+0.1) * gridWidth_;
    float y_start = (i+0.1) * gridHeight_;
    translate_x(x_start);
    translate_y(y_start);
    float width = 0.8 * gridWidth_;
    float height = 0.8 * gridHeight_;
    glVertex2f(x_start, y_start);
    glVertex2f(x_start + width, y_start);
    glVertex2f(x_start + width, y_start + height);
    glVertex2f(x_start, y_start + height);
}


void MazeDrawer::drawArrow(pair<int,int> lastStep, pair<int,int> nextStep){
    int dx = nextStep.second - lastStep.second;
    int dy = nextStep.first - lastStep.first;
    float middle_x = (lastStep.second + 0.5) * gridWidth_;
    float middle_y = (lastStep.first + 0.5) * gridHeight_;
    translate_x(middle_x);
    translate_y(middle_y);
    float vertex_x = middle_x + 0.5*gridWidth_ * dx;
    float vertex_y = middle_y + 0.5*gridHeight_ * dy;
    float left_x, right_x, left_y, right_y;
    if(dx){
        left_x = middle_x - 0.5 * gridWidth_ * dx;
        right_x = middle_x - 0.5 * gridWidth_ * dx;
        left_y = middle_y + 0.5 * gridHeight_;
        right_y = middle_y - 0.5 * gridHeight_;
    }
    else{
        left_y = middle_y - 0.5 * gridWidth_ * dy;
        right_y = middle_y - 0.5 * gridWidth_ * dy;
        left_x = middle_x - 0.5 * gridHeight_;
        right_x = middle_x + 0.5 * gridHeight_;
    }
    glVertex2f(vertex_x, vertex_y);
    glVertex2f(left_x, left_y);
    glVertex2f(middle_x, middle_y);
    glVertex2f(right_x, right_y);
}

void MazeDrawer::draw(Maze const & maze){
    gridWidth_ = (WIDTH-MARGIN) / (maze.numCols());
    gridHeight_ = (HEIGHT-MARGIN) / (maze.numRows());
    
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1,1,1);

    for(int i = 0; i < maze.numRows(); ++i){
        for(int j = 0; j < maze.numCols(); ++j){
            if(maze.get(i,j,0)){drawTop(i,j);}
            if(maze.get(i,j,1)){drawLeft(i,j);}
            if(maze.get(i,j,2)){drawBottom(i,j);}
            if(maze.get(i,j,3)){drawRight(i,j);}
        }
    }

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,0.5);
        for(int i = 0; i < maze.numRows(); ++i){
            for(int j = 0; j < maze.numCols(); ++j){
                if (maze.visited(i,j)){
                    drawMarker(i,j);   
                }
            }
        }
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0,1,0);

    pair<int, int> lastStep = maze.start();
    for (pair<int,int> step : maze.visitStack()){
        drawArrow(lastStep, step);
        lastStep = step;
    }
    glEnd();
    glutSwapBuffers();
    
}