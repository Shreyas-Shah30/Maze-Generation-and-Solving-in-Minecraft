#ifndef BUILD_MAZE_H
#define BUILD_MAZE_H

#include "Maze.h"
#include <mcpp/mcpp.h>

void flattenTerrain(mcpp::Coordinate& basePoint, int length, int width); 
void buildMaze(std::unique_ptr<Maze>& mazeObj);
void restoreTerrain(mcpp::Coordinate& basePoint);
void restoreTerrainEnhanced(mcpp::Coordinate& basePoint);
void buildMazeEnhanced(std::unique_ptr<Maze>& mazeObj);

#endif // BUILD_MAZE_H

