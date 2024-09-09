#include <climits>
#include <thread>
#include "solveMaze.h"
#include "menuUtils.h"
#include "Agent.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

void solveMaze(std::unique_ptr<Maze>& mazeObj, bool hasbeenPlaced){
     printSolveMazeMenu(); 
    int number = 0;
     std::cin >> number; 
     //user input validation check 
     while (std::cin.fail() || number < 1 || number > 3 || std::cin.eof()) {
     //check for control characters
      if (std::cin.eof()) {
     std::cout << "Input Error: Control Character Detected. "
     "Please Try Again From The Start." << std::endl;
     //exit the eof flag
     exit(EXIT_FAILURE);
     } 
     else{
     std::cout << "Input Error: Enter a number between 1 and 3." << std::endl;
     std::cin.clear();
     std::cin.ignore(INT_MAX, '\n');
     std::cin >> number; 
     }
}

     if(number == 1)
        {
         manualSolve(mazeObj);
         solveMaze(mazeObj, true);
        }
     else if(number == 2)
         {
            if (hasbeenPlaced){
         rightHandWalk();
            }
            else {
             std::cout << "Error: Please try to solve manually first." << std::endl; 
            }
         solveMaze(mazeObj, true);
         }
     else if(number == 3)
        {
         printMainMenu(); 
         }
     }

void PlaceBlocksToSolved(std::vector<Node*> path){
     mcpp::MinecraftConnection mc;
     // std::cout<<"Above"<<std::endl;
     // std::cout<<path.size()<<std::endl;
     // std::cout<<"Below"<<std::endl;

     for(unsigned int i = path.size()-1; i >=1; i--){
         // std::cout<< path[i]->coord<<std::endl;
          mc.setBlock(path[i]->coord, mcpp::Blocks::LIME_CARPET);
         std::this_thread::sleep_for(std::chrono::milliseconds(750));
         mc.setBlock(path[i]->coord, mcpp::Blocks::AIR);
         // Places blocks one by one in the path to retract it to the player.
    }
     std::cout<<"SOLVED BFS" << std::endl;
     //Prints solved when done.

}

void manualSolve(std::unique_ptr<Maze>& mazeObj) {
     std::vector<char*> mazeStruct = mazeObj->getMazeStruct();
     mcpp::MinecraftConnection mc;
     mcpp::Coordinate cellPos = *(mazeObj->getStart());
     bool trueD = false;
     bool mode = NORMAL_MODE;

 if (mode == TESTING_MODE) {    
     for (int j = mazeObj->getLength() - 1; j >= 0 && !trueD; --j) {
         for (int p = mazeObj->getWidth() - 1; p >= 0 && !trueD; --p) {
             if (mazeStruct[j][p] == '.') {
                 cellPos = *(mazeObj->getStart());
                 cellPos.x = cellPos.x + j;
                 cellPos.z = cellPos.z + p;
                 mc.setPlayerPosition(cellPos);
                 trueD = true;
             }  
          }
     }
} 
 else {
     std::vector<mcpp::Coordinate> cells;
      for (int j = 0; j < mazeObj->getLength(); ++j) {
         for (int p = 0; p < mazeObj->getWidth(); ++p) {
             if (mazeStruct[j][p] == '.') {
                 cellPos = *(mazeObj->getStart());
                 cellPos.x = cellPos.x + j;
                 cellPos.z = cellPos.z + p;
                 cells.push_back({cellPos});
                     
             }
         }
     }
int someIndex = std::rand() % cells.size();
mc.setPlayerPosition(cells[someIndex]);
    }
}

void rightHandWalk() {//searcha
mcpp::MinecraftConnection mc;
std::cout << "STARTING MAZE SOLVE" << std::endl;
mcpp::Coordinate pos = mc.getPlayerPosition();
bool solved = false;
Agent solver = Agent(pos);
solved = solver.IsSolved(pos);
AgentOrientation facing = X_PLUS;
     while(!solved) {
       // mc.setBlock(solver.GetPosition(), mcpp::Blocks::AIR);
        facing = solver.nextBlock(facing);
        solved = solver.IsSolved(solver.GetPosition());
       // mc.setBlock(solver.GetPosition(), mcpp::Blocks::LIME_CARPET);
       // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
     }

void BFSSolve(){
    //Establish Connection
     mcpp::MinecraftConnection mc;
     std::cout << "CALCULATING SHORTEST PATH..." << std::endl;
     mcpp::Coordinate pos = mc.getPlayerPosition();
     Node* startingNode = new Node(pos); 
     /* 
     * Create a new Node with the position as players position and
     * nullptr as previous Node. This is used later to retrace the path
     */ 
     Agent solver = Agent(pos); 
     //Agent gives us access to functions like GetNeighbours;
     std::vector<Node*> queue;
     queue.push_back(startingNode);
     std::vector<Node*> visited;
     /* 
     * Created two vectors to hold nodes that need to be 
     * checked and nodes that have already been checked.
     */
     visited.push_back(queue[0]);
     while(!queue.empty()){
        /*Loop runs until every node has been searched, at
         which no solution is found.*/
         Node* currentNode = queue[0];
         queue.erase(queue.begin());
         if(solver.IsSolved(currentNode->coord)){
            std::cout<<"SHORTEST PATH FOUND!" <<std::endl;
             std::cout<<"GENERATING PATH..." <<std::endl;
            std::vector<Node*> path;
            Node* curPtr = currentNode;
        /* 
        * This if statement checks if the solution is found and retraces 
        * the path using the previousNode pointer in the node structure
        */
            while(curPtr != nullptr){ 
                path.push_back(curPtr);
                curPtr = curPtr->previousNode;
            }

            PlaceBlocksToSolved(path);
             for(unsigned int i = 0; i < visited.size(); i++){
                 delete visited[i];
            }

            return;
         }
    std::vector<Node*> neighbours = solver.GetNeighbours(currentNode, visited);
                
        for(unsigned int i = 0; i < neighbours.size(); i++){
            queue.push_back(neighbours[i]);
            visited.push_back(neighbours[i]);   
        }
        /* 
        * Gets all neighbours and adds them to 
        * the visited queue as well as queue. This makes it so 
        * when we gather other neighbours later, we dont include duplicates 
        */

   }
   for(unsigned int i = 0; i < visited.size(); i++){
    delete visited[i];
   }
   std::cout<<"MAZE IS UNSOLVEABLE, COULD NOT GENERATE PATH."<<std::endl;
}