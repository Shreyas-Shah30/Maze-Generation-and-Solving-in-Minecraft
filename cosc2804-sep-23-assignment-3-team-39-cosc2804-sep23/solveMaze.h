#ifndef SOLVE_MAZE_H
#define SOLVE_MAZE_H

#include "Maze.h"
#include <mcpp/mcpp.h>
#include <memory>

void solveMaze(std::unique_ptr<Maze>& mazeObj, bool hasbeenPlaced);
void rightHandWalk();
void BFSSolve();
void manualSolve(std::unique_ptr<Maze>& mazeObj);

#endif // SOLVE_MAZE_H

