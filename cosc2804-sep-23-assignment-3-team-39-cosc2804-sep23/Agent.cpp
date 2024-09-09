#include "Agent.h"

Agent::Agent(mcpp::Coordinate startLoc)
{
    currentLoc = startLoc;
    step = 0;
}

Agent::~Agent()
{
}

mcpp::Coordinate Agent::GetPosition() {
    return currentLoc;
}

bool Agent::IsSolved(mcpp::Coordinate pos) {
    // checks if all cross points are empty then at least 2 corners
    bool solved = false;
    //cross points
        if (!(mc.getBlock(pos + MOVE_XPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)
        && !(mc.getBlock(pos + MOVE_XMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)
        && !(mc.getBlock(pos + MOVE_ZPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK) 
        && !(mc.getBlock(pos + MOVE_ZMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)
        ) {
        // corners
        int count = 0;
       
        if(!(mc.getBlock(pos + MOVE_XPLUS + MOVE_ZPLUS)
        == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            ++count;
        }
        
        if(!(mc.getBlock(pos + MOVE_XMINUS + MOVE_ZPLUS)
        == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            ++count;
        }
        
        if(!(mc.getBlock(pos + MOVE_XPLUS + MOVE_ZMINUS)
        == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            ++count;
        }
        
        if(!(mc.getBlock(pos + MOVE_XMINUS + MOVE_ZMINUS)
        == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            ++count;
        }

        
        if (count > 0){
            solved = true;
        }
                
        }
        return solved;
        }
    



AgentOrientation Agent::nextBlock(AgentOrientation facing) {
    /* depending on direction facing move check and move to a different block
     * check block to the right then if not wood face right and move 1
     * if there check block in front if not wood move 1 foward
     * if there face left
     */ 
    mcpp::Coordinate pos = currentLoc;
    if(facing == X_PLUS)  {
      if(!(mc.getBlock(pos + MOVE_ZPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            facing = Z_PLUS;
           currentLoc = currentLoc + MOVE_ZPLUS;
           placeCarpetOnce(currentLoc);
        }
      else if(!(mc.getBlock(pos + MOVE_XPLUS)
      == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            currentLoc = currentLoc + MOVE_XPLUS;
            placeCarpetOnce(currentLoc);
        }
        else {
            facing = Z_MINUS;
        }
    }
    else if(facing == Z_PLUS)  {
     if(!(mc.getBlock(pos + MOVE_XMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            facing = X_MINUS;
            currentLoc = currentLoc + MOVE_XMINUS;
            placeCarpetOnce(currentLoc);
        }
     else if(!(mc.getBlock(pos + MOVE_ZPLUS)
     == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            currentLoc = currentLoc + MOVE_ZPLUS;
            placeCarpetOnce(currentLoc);
        }
        else {
            facing = X_PLUS;
        }
    }       
    
    else if(facing == Z_MINUS)  {
      if(!(mc.getBlock(pos + MOVE_XPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            facing = X_PLUS;
            currentLoc = currentLoc + MOVE_XPLUS;
            placeCarpetOnce(currentLoc);
        }
        else if(!(mc.getBlock(pos + MOVE_ZMINUS)
        == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            currentLoc = currentLoc + MOVE_ZMINUS;
            placeCarpetOnce(currentLoc);
        }
        else {
            facing = X_MINUS;
        }
        
    }
    else if(facing == X_MINUS)  {
     if(!(mc.getBlock(pos + MOVE_ZMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            facing = Z_MINUS;
            currentLoc = currentLoc + MOVE_ZMINUS;
            placeCarpetOnce(currentLoc);
        }
     else if(!(mc.getBlock(pos + MOVE_XMINUS) 
      == mcpp::Blocks::ACACIA_WOOD_PLANK)) {
            currentLoc = currentLoc + MOVE_XMINUS;
            placeCarpetOnce(currentLoc);
        }
        else {
            facing = Z_PLUS;
        }
    }
    return facing;
}

std::vector<Node*> Agent::GetNeighbours(Node* currentNode, 
std::vector<Node*> visited){
    std::vector<Node*> neighbours;
    mcpp::Coordinate currentPos = currentNode->coord;   

    if(mc.getBlock(currentPos + MOVE_XPLUS) == mcpp::Blocks::AIR 
    && !checkIfVisited(currentPos + MOVE_XPLUS, visited)){
     //Get the block at the current block plus offset in 4 cardinal directions.
        Node* neighbour = new Node(currentPos + MOVE_XPLUS, currentNode);
        neighbours.push_back(neighbour);
    }
    if(mc.getBlock(currentPos + MOVE_XMINUS) == mcpp::Blocks::AIR
    && !checkIfVisited(currentPos + MOVE_XMINUS, visited)){
        Node* neighbour = new Node(currentPos + MOVE_XMINUS,currentNode);
        neighbours.push_back(neighbour);
    }
     if(mc.getBlock(currentPos + MOVE_ZPLUS) == mcpp::Blocks::AIR
     && !checkIfVisited(currentPos + MOVE_ZPLUS, visited)){
        Node* neighbour = new Node(currentPos + MOVE_ZPLUS,currentNode);
        neighbours.push_back(neighbour);
    }
     if(mc.getBlock(currentPos + MOVE_ZMINUS) == mcpp::Blocks::AIR
     && !checkIfVisited(currentPos + MOVE_ZMINUS, visited)){
        Node* neighbour = new Node(currentPos + MOVE_ZMINUS,currentNode);
        neighbours.push_back(neighbour);
    }
    //Adds each neighbour to the neighbours array

    return neighbours;

}

bool Agent::checkIfVisited(mcpp::Coordinate pos, std::vector<Node*> visited){
    /*
    * Checks if the neighbour exists in the visited vector 
    * before adding it as a neighbour
    */ 
    bool returnBool = false;
    for(unsigned int i = 0; i < visited.size(); i++){
        //std::cout<<"Visited[" << i << "] " << visited[i].coord << std::endl;
        if(visited[i]->coord == pos){
            returnBool = true;
        }
    }
    return returnBool;
}
// place carpet and print out step then wait and delte carpet
void Agent::placeCarpetOnce(mcpp::Coordinate pos) {
        mc.setBlock(pos, mcpp::Blocks::LIME_CARPET);
        std::cout << "Step[" << step << "]: (" << pos.x << ", " 
        << pos.y << ", " << pos.z << ")" << std::endl;
        ++step;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        mc.setBlock(pos, mcpp::Blocks::AIR);
}