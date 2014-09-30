#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <list>

using std::list;
using std::vector;
using std::pair;

class Maze{
public:
    Maze(int numRows, int numCols, pair<int,int> start, pair<int, int> finish);
    bool get(int i,int j,int k)const;
    void print();
    int numRows()const;
    int numCols()const;
    pair<int, int> step();
    bool visited(int i, int j)const;
    list<pair<int, int> > visitStack() const;
    pair<int, int> start() const;
    
private:
    int numRows_;
    int numCols_;
    //Tensor3 * mazeTensor;
    vector<vector<vector<int> > >  mazeVector_;
    list<pair<int, int> > visitStack_;
    vector<vector<bool> > visited_;
    pair<int, int> start_;
    pair<int, int> finish_;
};

#endif