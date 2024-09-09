#include <memory>
#include <vector>
#include <climits>
#include <tuple>
#include "generateMaze.h"
#include "menuUtils.h"

//handle valid inputs
void handleInvalidInput() {
//Contract: error handling for control characters
if (std::cin.eof()) {
     std::cout << "Input Error: Control Character Detected. "
                 "Please Try Again From The Start." << std::endl;
     //exit the eof flag
     exit(EXIT_FAILURE);
} 
else {
     /*
     * Contract: user validation to check if the number is a number 
     * and is between and including 1 and 3
     */ 
     std::cout << "Input Error: Enter a number between 1 and 3." << std::endl;
     std::cin.clear();
     std::cin.ignore(INT_MAX, '\n');
     }
 }

//get input coordinates
void getInputCoordinates(int& x, int& y, int& z) {
mcpp::MinecraftConnection mc;
bool validBasePoint = false;
while (!validBasePoint) {
  if (std::cin >> x >> y >> z) {
  int height = mc.getHeight(x, z);
  /*
  * Contract: check to see if the player is not at a suitable location,
  * (below the ground and in the air), if so then display an error message,
  * for building a maze at the same basePoint, the if statement to check if
  * the block is ACACIA WOOD PLANK is required otherwise it will assume the
  * coordinates entered are in the ground
  */
   if (y > height + 2){
    std::cout << "Input Error: The coordinates entered are in the air. "
     "Please enter coordinates exactly one unit above the ground."<< std::endl;
   }
    else if(y <= height){
        if(mc.getBlock(mcpp::Coordinate(x, y + 2, z)) == 
        mcpp::Blocks::ACACIA_WOOD_PLANK){
            validBasePoint = true; 
        }
        else{
     std::cout << "Input Error: The coordinates entered are in the ground. "
     "Please enter coordinates exactly one unit above the ground."<< std::endl;
        }
    }
   /*
   * Contract: error handling if user doesn't enter a y-coordinate 
   * of one unit above the ground or if the y-coordinate is too large
   */
   else if (y == height + 1) {
      std::cout << "Input Error: Please enter a y-coordinate exactly "
      "one unit above the ground." << std::endl;
        } 
        else {
            validBasePoint = true;
        }
    }
     else{
      //Contract: error handling for control characters
      if (std::cin.eof()) {
         std::cout << "Input Error: Control Character Detected. "
                      "Please Try Again From The Start." << std::endl;
         //exit the eof flag             
         exit(EXIT_FAILURE);
      }
      else {
         /* 
         * Contract: user validation for checking to see 
         * if basePoint coordinates are all numbers
         */
         std::cout << "Input Error: Please enter 3 valid "
         "numbers for x, y, z." << std::endl;
         std::cin.clear();
         std::cin.ignore(INT_MAX, '\n');
       }
     }
  }
}

void getInputCoordinatesEnhanced(int& x, int& y, int& z) {
mcpp::MinecraftConnection mc;
bool validBasePoint = false;
while (!validBasePoint) {
  if (std::cin >> x >> y >> z) {
  /*
  * Contract: check to see if the player is not at a suitable location,
  * (in the air), if so then display an error message
  */
   int height = mc.getHeight(x, z);
   if (y > height + 2) {
      std::cout << "Input Error: The coordinates entered are in the air. "
      "Please enter coordinates exactly one unit above the ground." 
      << std::endl;
   }
   /*
   * Contract: error handling if user doesn't enter a y-coordinate 
   * of one unit above the ground or if the y-coordinate is too large
   */
        else {
            validBasePoint = true;
        }
    }
     else{
      //Contract: error handling for control characters
      if (std::cin.eof()) {
         std::cout << "Input Error: Control Character Detected. "
                      "Please Try Again From The Start." << std::endl;
         //exit the eof flag             
         exit(EXIT_FAILURE);
      }
      else {
         /* 
         * Contract: user validation for checking to see 
         * if basePoint coordinates are all numbers
         */
         std::cout << "Input Error: Please enter 3 valid "
         "numbers for x, y, z." << std::endl;
         std::cin.clear();
         std::cin.ignore(INT_MAX, '\n');
       }
     }
  }
}

//get input dimensions
void getInputDimensions(int& length, int& width) {
 bool validLengthWidth = false;
 while (!validLengthWidth) {
     std::cin >> length >> width;
     //sets boolean variable to true to length and width are valid numbers
 if (!std::cin.fail() && length % 2 != 0 && width % 2 != 0 && length > 0 
     && width > 0) {
      validLengthWidth = true; 
 } 
 else {
 //error handling for control characters
 if (std::cin.eof()) {
     std::cout << "Input Error: Control Character Detected. "
                 "Please Try Again From The Start." << std::endl;
     //exit the eof flag
     exit(EXIT_FAILURE);
 } 
 else if (length < 0 || width < 0) {
     /*
     * Contract: check to see if length and width are positive number, 
     * if not then error message is outputted 
     */
     std::cout << "Length and width should be "
     "non-negative numbers." << std::endl;
     std::cin.clear();
     std::cin.ignore(INT_MAX, '\n');
     } 
 else {
     //Contract: checks if length and width are odd numbers
     std::cout << "Length and width should be odd numbers." << std::endl;
     std::cin.clear();
     std::cin.ignore(INT_MAX, '\n');
    }
         }
     }
}

bool hasSingleEntranceOrExit(std::vector<std::unique_ptr<char[]>>& maze, 
int length, int width) {
int count = 0;
bool isValid = true;
//Contract: check top and bottom rows for entrances/exits, only if length > 1
if (length > 1) {
     for (int j = 0; j < width; j++) {
         if (maze[0][j] == '.') {
                 count++;
         }
            if (maze[length - 1][j] == '.') {
                 count++;
         }
    }
}
//Contract: check left and right columns for entrances/exits only if width > 1
if (width > 1) {
     for (int i = 1; i < length - 1; i++) {
         if (maze[i][0] == '.') {
                 count++;
         }
         if (maze[i][width - 1] == '.') {
                 count++;
           }
     }
}
//if the maze has a length or width of one then directly check the cells
if (length == 1 || width == 1) {
     for (int i = 0; i < length; i++) {
         for (int j = 0; j < width; j++) {
             if (maze[i][j] == '.') {
                    count++;
             }
         }
    }
}
if (count != 1) {
     isValid = false;
}
     return isValid;
}

void printMaze(std::unique_ptr<Maze>& mazeObj, int x, int y, int z) {
     //print the maze structure 
     std::cout << "**Printing Maze**" << std::endl;
     std::cout << "BasePoint: (" << x << ", " << y << ", " << z << ")" 
     << std::endl;
     std::cout << "Structure:" << std::endl;
     auto mazeStructure = mazeObj->getMazeStruct();
     for (int i = 0; i < mazeObj->getLength(); i++) {
         for (int j = 0; j < mazeObj->getWidth(); j++) {
             std::cout << mazeStructure[i][j];
         }
         std::cout << std::endl;
    }
     std::cout << "**End Printing Maze**" << std::endl;
}

//get a manually defined maze
std::unique_ptr<Maze> getManualMaze(mcpp::Coordinate& basePoint, 
int length, int width, bool mode) {
std::vector<std::unique_ptr<char[]>> tempMazeStructure;
std::cout << "Enter the maze structure:" << std::endl;
std::cin.ignore();

//check if the maze structure has been completely and correctly inputted
bool isComplete = false; 

  while (!isComplete) {
    tempMazeStructure.clear();
     //assume maze structure is valid initially 
     bool validMazeInput = true;
     for (int i = 0; i < length && validMazeInput; i++) {
         std::string row;
         std::getline(std::cin, row);
     if (static_cast<int>(row.length()) != width || row.find_first_not_of("x.")
     != std::string::npos) {
     /*
     * Contract: check if invalid row is entered, then set 
     * validMazeInput to false to redo the input process
     */
     if (std::cin.eof()) {
     std::cout << "Input Error: Control Character Detected. "
     "Please Try Again From The Start." << std::endl;
     exit(EXIT_FAILURE);
     }
     if (static_cast<int>(row.length()) != width) {
     std::cout << "Input Error: The row entered doesn't match the maze width. "
     "Please re-enter the entire maze structure." << std::endl;
     } 
     else {
     std::cout << "Input Error: The row entered contains invalid characters. "
     "Please re-enter the entire maze structure." << std::endl;
     }
     //reset the maze input to false as maze structure is invalid
     validMazeInput = false;
     } 
     else {
     auto arrayRow = std::make_unique<char[]>(width);
     for (int j = 0; j < width; j++) {
      arrayRow[j] = row[j];
      }
     tempMazeStructure.push_back(std::move(arrayRow));
         }
     }

     if (validMazeInput) {
     if (hasSingleEntranceOrExit(tempMazeStructure, length, width)) {
     /*
     * if maze structure is valid and has a single entrance/exit, 
     * set isComplete to true
     */
        isComplete = true; 
     } 
     else {
     std::cout << "Input Error: The maze should have one entrance/exit. "
     "Please re-enter the maze structure." << std::endl;
    }
  }
}

      auto mazeObj = std::make_unique<Maze>(basePoint, length, width, mode);
     mazeObj->setMazeStruct(std::move(tempMazeStructure));
     return mazeObj;
}

std::unique_ptr<Maze> getRandomMaze(mcpp::Coordinate& basePoint, 
int length, int width, bool mode) {
     //generate random maze using Maze class functions 
     auto mazeObj = std::make_unique<Maze>(basePoint, length, width, mode);
     mazeObj->generateRandomMaze(mode);
     return mazeObj;
}

std::unique_ptr<Maze> getRandomMazeEnhanced(mcpp::Coordinate& basePoint, 
int length, int width, bool mode) {
     //generate random maze using Maze class functions 
     auto mazeObj = std::make_unique<Maze>(basePoint, length, width, mode);
     mazeObj->generateRandomMazeEnhanced(mode);
     return mazeObj;
}

std::tuple<bool, std::unique_ptr<Maze>, mcpp::Coordinate, int, int> 
generateMaze(bool mode) {
     //generate the maze
     printGenerateMazeMenu();
     int mazeNumber = 0;
     int x_coord = 0;
     int y_coord = 0;
     int z_coord = 0; 
     bool newMazeGenerated = false;
     std::cin >> mazeNumber;
     mcpp::Coordinate basePoint; 
     int length = 0;             
     int width = 0;     
     std::unique_ptr<Maze> mazeObj;

     //Contract: user validation using functions listed above
     while (std::cin.fail() || mazeNumber < 1 || mazeNumber > 3) {
         handleInvalidInput();
         std::cin >> mazeNumber;
     }

     if (mazeNumber == 1 || mazeNumber == 2) {
         std::cout << "Enter the basePoint of the maze:" << std::endl;
         getInputCoordinates(x_coord, y_coord, z_coord);
         basePoint = mcpp::Coordinate(x_coord, y_coord, z_coord);

         std::cout << "Enter the length and width of the maze:" << std::endl;
         getInputDimensions(length, width);
     }

     if (mazeNumber == 1) {
         mazeObj = getManualMaze(basePoint, length, width, mode);
         std::cout << "Maze read successfully" << std::endl;
          printMaze(mazeObj, x_coord, y_coord, z_coord);
         printMainMenu();
         newMazeGenerated = true;
      }

     else if (mazeNumber == 2) {
         mazeObj = getRandomMaze(basePoint, length, width, mode);
         std::cout << "Maze generated successfully" << std::endl;
         printMaze(mazeObj, x_coord, y_coord, z_coord);
         printMainMenu(); 
         newMazeGenerated = true;
    }

     else if (mazeNumber == 3) {
         printMainMenu();
    }
     return std::make_tuple(newMazeGenerated, std::move(mazeObj), 
     basePoint, length, width);
}

std::tuple<bool, std::unique_ptr<Maze>, mcpp::Coordinate, int, int> 
generateMazeEnhanced(bool mode) {
     //generate the maze
     int x_coord = 0;
     int y_coord = 0;
     int z_coord = 0; 
     bool newMazeGenerated = false;
     mcpp::Coordinate basePoint; 
     int length = 0;             
     int width = 0;     
     std::unique_ptr<Maze> mazeObj;

     //Contract: user validation using functions listed above
         std::cout << "Enter the basePoint of the maze:" << std::endl;
         getInputCoordinatesEnhanced(x_coord, y_coord, z_coord);
         basePoint = mcpp::Coordinate(x_coord, y_coord, z_coord);

         std::cout << "Enter the length and width of the maze:" << std::endl;
         getInputDimensions(length, width);



         mazeObj = getRandomMazeEnhanced(basePoint, length, width, mode);
         std::cout << "Maze generated successfully" << std::endl;
         printMaze(mazeObj, x_coord, y_coord, z_coord);
         newMazeGenerated = true;

     return std::make_tuple(newMazeGenerated, std::move(mazeObj), 
     basePoint, length, width);
}
