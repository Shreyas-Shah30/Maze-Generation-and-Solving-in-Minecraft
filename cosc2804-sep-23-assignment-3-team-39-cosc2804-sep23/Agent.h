#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <mcpp/mcpp.h>
#include "Node.h"
#include <vector>
#include <thread>

#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

enum solveAlgorithm{
        RIGHT_HAND_FOLLOW,
        BREATH_FIRST_SEARCH,
};

enum AgentOrientation{
    X_PLUS,
    Z_PLUS,
    X_MINUS,
    Z_MINUS
};

class Agent
{

public:
    Agent(mcpp::Coordinate startLoc);
    ~Agent();
    bool IsSolved(mcpp::Coordinate);
    AgentOrientation nextBlock(AgentOrientation facing);
    void rightHandWalk();
    std::vector<Node*> GetNeighbours(Node*, std::vector<Node*>);
    bool checkIfVisited(mcpp::Coordinate, std::vector<Node*>);
    mcpp::Coordinate GetPosition();
    void placeCarpetOnce(mcpp::Coordinate pos);


private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate currentLoc;
    int step;

};



#endif //ASSIGN3_AGENT_H