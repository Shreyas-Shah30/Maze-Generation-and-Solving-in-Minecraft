#include <iostream>
#include <vector> 
#include <memory>
#include <climits>
#include <tuple> 
#include <mcpp/mcpp.h>
#include "menuUtils.h"
#include "Maze.h"
#include "generateMaze.h"
#include "solveMaze.h"
#include "buildMaze.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States {
    ST_Main,
    ST_Exit
};
void runEnhancements(std::unique_ptr<Maze>& mazeObj);

int main(int argc, char* argv[]) {
mcpp::MinecraftConnection mc;
std::unique_ptr<Maze> mazeObj;
mcpp::Coordinate basePoint;
bool mode = NORMAL_MODE;

    //implement testing mode
  if (argc > 1 && std::string(argv[1]) == "-testmode") {
      mode = TESTING_MODE;
   }

  mc.doCommand("time set day"); 

  States curState = ST_Main;
  printStartText(); 
  printMainMenu();
    

  //State machine for menu
  while (curState != ST_Exit) {
     int userNumber = 0;

     std::cin >> userNumber; 

     /* 
     * Contract: user input validation check to see if 
     * userNumber is between and including 1 and 6
     */
   while (std::cin.fail() || userNumber < 1 || userNumber > 6 
   || std::cin.eof()) {
     //Contract: check for control characters
     if (std::cin.eof()) {
         std::cout << "Input Error: Control Character Detected. "
                      "Please Try Again From The Start." << std::endl;
         //exit the eof flag
         exit(EXIT_FAILURE);
         } 
     else {
         std::cout << "Input Error: Enter a number between "
         "1 and 6." << std::endl;
         std::cin.clear();
         std::cin.ignore(INT_MAX, '\n');
         std::cin >> userNumber; 
         }
         }

    if (userNumber == 1) { 
         //intialise variables to account for new maze generations
         bool newMazeGenerated = false; 
         std::unique_ptr<Maze> newMazeObj;
         mcpp::Coordinate newBasePoint;
         int length = 0;
         int width = 0;
            
         std::tie(newMazeGenerated, newMazeObj, newBasePoint, length, 
         width) = generateMaze(mode);
            
         //only overwrite the maze if a new one was actually generated
         if (newMazeGenerated) {
             mazeObj = std::move(newMazeObj);
             basePoint = newBasePoint;
         }
     } 
     else if (userNumber == 2) {
         /* 
         * Contract: build the maze if the user has first generated it, 
         * if not then output error message 
         */
         if (mazeObj) {
             buildMaze(mazeObj);
         } 
         else {
             std::cout << "Error: Maze not initialized. "
             "Please generate the maze first." << std::endl;
         }
         printMainMenu();
         }
     else if (userNumber == 3) {
         if (mazeObj) {
             solveMaze(mazeObj, false); //g
         } 
         else {
             std::cout << "Error: Maze not initialized. "
             "Please generate the maze first." << std::endl;
             printMainMenu();
         }
         }
     else if (userNumber == 4) {
         printEnhancements();
         runEnhancements(mazeObj);
    }
     else if (userNumber == 5) {
         printTeamInfo();
         printMainMenu(); 
     }
     else if (userNumber == 6) {
         restoreTerrain(basePoint);
         restoreTerrainEnhanced(basePoint);
         //reset maze object
         mazeObj.reset();
         printExitMassage(); 
         curState = ST_Exit; 
     }
}

   return EXIT_SUCCESS;
}

void runEnhancements(std::unique_ptr<Maze>& mazeObj) {
mcpp::MinecraftConnection mc;
mcpp::Coordinate basePoint;
bool mode = NORMAL_MODE;
int enhancementNumber = 0;
bool validNum = false; 
/*
* user input validation check to see if userNumber is 
* between and including 1 and 3
*/
     while(!validNum){
     std::cin >> enhancementNumber; 
     //check for control characters
     if (std::cin.eof()) {
         std::cout << "Input Error: Control Character Detected. "
                       "Please Try Again From The Start." << std::endl;
         //exit the eof flag
         exit(EXIT_FAILURE);
     } 
     if(enhancementNumber < 1 || enhancementNumber > 3) {
     std::cout << "Input Error: Enter a number between 1 and 3." << std::endl;
     std::cin.clear();
     std::cin.ignore(INT_MAX, '\n');
    }
     else{
        validNum = true; 
        }
        }
     if(enhancementNumber == 1){
         //do make with obsticles
         
         bool newMazeGenerated = false; 
         std::unique_ptr<Maze> newMazeObj;
         mcpp::Coordinate newBasePoint;
         int length = 0;
         int width = 0;
            
         std::tie(newMazeGenerated, newMazeObj, newBasePoint, length, 
         width) = generateMazeEnhanced(mode);
            
         //only overwrite the maze if a new one was actually generated
         if (newMazeGenerated) {
             mazeObj = std::move(newMazeObj);
             basePoint = newBasePoint;
         }
         std::cout << std::endl;
        
         buildMazeEnhanced(mazeObj);
    
         printMainMenu();
     }
    else if(enhancementNumber == 2) {
     if(mazeObj){
        BFSSolve();
     }
     else{
         std::cout << "Error: Maze not initialized. "
         "Please generate the maze first." << std::endl;
     }
        printMainMenu();
     }
     else if(enhancementNumber == 3) {
        printMainMenu();
     }
}