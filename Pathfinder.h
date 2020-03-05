#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <string>
#include <iostream>

#include "PathfinderInterface.h"

using namespace std;

class Pathfinder : public PathfinderInterface {

private:
    int maze[5][5][5];
    vector <string> P;
    
public:
    Pathfinder() {}
    ~Pathfinder() {}
    
	string toString() const;
	
	void createRandomMaze();
	
    bool importMaze(string file_name);
	
	vector<string> solveMaze();
	
	bool findPath(int x, int y, int z);

};
#endif