#include "maze.h"
#include <stdlib.h>
#include <unistd.h>
#include <GLUT/glut.h>
#include <list>
#include <stdlib.h>
#include <utility>
#include <iostream>
#include "MazeUnix.cpp" 


using std::list;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

Maze::Maze(int numRows, int numCols,  pair<int,int> start, pair<int, int> finish){
    numRows_ = numRows;
    numCols_ = numCols;
    createMaze(mazeVector_, numRows, numCols, 1);
    start_ = start;
    finish_ = finish;
    visited_ = * new vector<vector<bool> >(numRows_, vector<bool>(numCols_, false));
    visited_[start_.first][start_.second] = true;
    visitStack_.push_back(start_);
    print();
    
}

bool Maze::get(int i, int j, int k)const{
    return mazeVector_[i][j][k];
}

list<pair<int, int> > Maze::visitStack() const{
    return visitStack_;
}

void Maze::print(){
    for(int i = numRows_ - 1; i >= 0; --i){
        for(int j = 0; j < numCols_; ++j){
            cout << "|" << get(i,j,0) << ":" << get(i,j,1)
                <<":" << get(i,j,2) << ":" << get(i,j,3) << ":";
        }
        cout << endl;
    }

}

int Maze::numRows() const{
    return numRows_;
}

int Maze::numCols() const{
    return numCols_;
}

bool Maze::visited(int i, int j) const{
    return visited_[i][j];
}

pair<int,int> Maze::start() const{
    return start_;
}

pair<int,int> Maze::step(){
    pair<int,int> toVisit;
    int bestManhattan = -1;
    pair<int,int> current = visitStack_.back();
    if(current == finish_){return current;}
    //up
    bool inBounds = (current.first < numRows() - 1);
    bool notVisited = (inBounds && !visited_[current.first + 1][current.second]);
    bool canVisit = (notVisited && !get(current.first, current.second, 2));
    if(canVisit){
        int manhattan = abs(finish_.first - current.first) + abs(finish_.second - (current.second + 1));
        if(manhattan < bestManhattan || bestManhattan == -1){
            bestManhattan = manhattan;
            toVisit = make_pair(current.first + 1, current.second);
        }
    }
    //left
    inBounds = (current.second > 0);
    notVisited = (inBounds && !visited_[current.first][current.second - 1]);
    canVisit = (notVisited && !get(current.first, current.second, 1));
    if(canVisit){
        int manhattan = abs(finish_.first - (current.first-1)) + abs(finish_.second - current.second);
        if(manhattan < bestManhattan || bestManhattan == -1){
            bestManhattan = manhattan;
            toVisit = make_pair(current.first, current.second - 1);
        }
    }
    //down
    inBounds = (current.first > 0);
    notVisited = (inBounds && !visited_[current.first - 1][current.second]);
    canVisit = (notVisited && !get(current.first, current.second, 0));
    if(canVisit){
        int manhattan = abs(finish_.first - current.first) + abs(finish_.second - (current.second-1));
        if(manhattan < bestManhattan || bestManhattan == -1){
            bestManhattan = manhattan;
            toVisit = make_pair(current.first - 1, current.second);
        }
    }
    //right
    inBounds = (current.second < numCols() - 1);
    notVisited = (inBounds && !visited_[current.first][current.second + 1]);
    canVisit = (notVisited && !get(current.first, current.second, 3));
    if(canVisit){
        int manhattan = abs(finish_.first + 1 - current.first) + abs(finish_.second - current.second);
        if(manhattan < bestManhattan || bestManhattan == -1){
            bestManhattan = manhattan;
            toVisit = make_pair(current.first, current.second + 1);
        }
    }
    if(bestManhattan == -1){//nothing possible
        if (visitStack_.empty()){
            cout<<"out of options" << endl;
        }
        else{
            visitStack_.pop_back();
        }
        pair<int, int> rtn = visitStack_.back();
        return rtn;
    }
    else{//something possible
        visitStack_.push_back(toVisit);
        visited_[toVisit.first][toVisit.second] = true;
        return toVisit;
    }
}