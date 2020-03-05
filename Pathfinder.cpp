#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include "Pathfinder.h"

using namespace std;

string Pathfinder::toString() const {
    bool emptymaze = true;
    string str = "";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                     str.append(to_string(maze[i][j][k]));
                     //add a space after each element, except the last in the line
                     if (k != 4) {
                         str.append(" ");
                     }
                     else { str.append("\n"); } //add a new line after the last element in a row
                     
                     //if all elements of the maze are 0s, then emptymaze will return true
                     if (emptymaze == true && maze[i][j][k] == 1) {
                         emptymaze = false;
                     }
                }
            }
            if (i != 4) { str.append("\n"); }
        }
    
    
    //return a maze of 1s
    if (emptymaze == true || (emptymaze == false && (maze[0][0][0] != 1 || maze[4][4][4] != 1))) {
        str = "1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n";
        str.append("1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n");
        str.append("1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n");
        str.append("1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n\n");
        str.append("1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n1 1 1 1 1\n");
    }
    
    return str;
}
	
void Pathfinder::createRandomMaze() {
    maze[0][0][0] = 1;
    maze[4][4][4] = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                maze[i][j][k] = rand()%2;
            }
        }
    }
}
	/*
	Reads in a maze from a file with the given file name and stores it as the current maze.
	* Does nothing if the file does not exist or if the file's data does not represent a valid
	* maze.
	*
	* The file's contents must be of the format described above to be considered valid
	*
	* Parameter:	file_name
	*				The name of the file containing a maze
	* Returns:		bool
	*				True if the maze is imported correctly; false otherwise
	*/
bool Pathfinder::importMaze(string file_name) {
    ifstream inFile;
    inFile.open(file_name.c_str());
    
    //if the file does not exist;
    if (inFile == NULL) {
        return false;
    }
    vector <int> mazeVector;
    string current;
    int c = 0; //counter should go to 125
    int value;
    while (inFile >> current) {
        if (current.length() != 1) {
            return false;
        }
        value = atoi(current.c_str());
        if (value > 1 || value < 0) {
            return false;
        }
        //first and last values in the maze must equal 1
        if ( c == 0 || c == 124 ) {
            if ( value != 1 ) { return false; }
        }
        mazeVector.push_back(value);
        c++;
    }
    //125 values read in from file;
    if (c != 125 && mazeVector.size() != 125) {
        return false;
    }
    //import maze into object
    c = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                maze[i][j][k] = mazeVector.at(c);
                c++;
            }
        }
    }
    return true;
    
    
}
	
vector<string> Pathfinder::solveMaze() {
    bool solve;
    P.clear();
    solve = findPath(0,0,0);
    //if (solve) { cout << "SOLVABLE\n"; }
    //else { cout << "UNSOLVABLE\n";}
    //change all 2s back to 1s
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (maze[i][j][k] == 2) {
                    maze[i][j][k] = 1;
                }
            }
        }
    }
    //print coordinates
    /*if (solve) { cout << "SOLVABLE\n"; }
    else { cout << "UNSOLVABLE\n";}
    for (int i = 0; i < P.size(); i++) {
        cout << P.at(i) << endl;
    }*/
    return P;
    
}

bool Pathfinder::findPath(int x, int y, int z) {
    stringstream str;
    str << "(" << z << ", " << y << ", " << x << ")";
    P.push_back(str.str());
    //Base Cases
    //outside the maze? //invalid path? been here before?
    if ( x < 0 || x > 4 || y < 0 || y > 4 || z < 0 || z > 4 || maze[x][y][z] == 0 || maze[x][y][z] == 2) {
        P.pop_back();
        return false;
    }
    //end of maze?
    if (x == 4 && y == 4 && z == 4) {
        return true;
    }
    maze[x][y][z] = 2;
    
    //RECURSIONNNNN
    
    if ( findPath(x,y-1,z) || findPath(x,y+1,z) || findPath(x-1,y,z) || findPath(x+1,y,z) || findPath(x,y,z-1) || findPath(x,y,z+1) ) {
        return true;
    }
    else {
        P.pop_back();
        return false;
    }
    
}