#ifndef GENERATE_MAZE_H
#define GENERATE_MAZE_H

#include "Maze.h"
#include <mcpp/mcpp.h>

void getInputCoordinates(int& x, int& y, int& z);
void getInputCoordinatesEnhanced(int& x, int& y, int& z);
void getInputDimensions(int& length, int& width);
void printMaze(std::unique_ptr<Maze>& mazeObj, int x, int y, int z);
//define tuple to store variables 
std::tuple<bool, std::unique_ptr<Maze>, mcpp::Coordinate, int, int>
generateMaze(bool mode);
std::tuple<bool, std::unique_ptr<Maze>, mcpp::Coordinate, int, int> 
generateMazeEnhanced(bool mode);


#endif // GENERATE_MAZE_H

