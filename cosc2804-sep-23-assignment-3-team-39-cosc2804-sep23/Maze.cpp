#include "Maze.h"
#include <algorithm>
#include <ctime>

Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen,
bool mode) {
     this->length = xlen;
     this->width = zlen;
     this->start = std::make_unique<mcpp::Coordinate>
     (basePoint.x, basePoint.y, basePoint.z);
     this->mode = mode;
     this->mazeStruct.resize(this->length);
     //set all characters of maze structure as 'x' intially 
     for (int i = 0; i < this->length; i++) {
         this->mazeStruct[i] = std::make_unique<char[]>(this->width);
         std::fill(this->mazeStruct[i].get(), this->mazeStruct[i].get()
         + this->width, 'x');
     }
}

int Maze::getLength() {
     return this->length;
}

int Maze::getWidth() {
     return this->width;
}

void Maze::setLength(int length) {
     this->length = length;
}

void Maze::setWidth(int width) {
     this->width = width;
}

void Maze::setStart(std::unique_ptr<mcpp::Coordinate> newStart) {
     this->start = std::move(newStart);
}

mcpp::Coordinate* Maze::getStart() {
    return start.get();
}

void Maze::setMazeStruct(std::vector<std::unique_ptr<char[]>> mazeStructArray){
     this->mazeStruct = std::move(mazeStructArray);
}

std::vector<char*> Maze::getMazeStruct() {
     //get the maze structure using smart pointers
     std::vector<char*> tmpStruct;
     for (auto& row : mazeStruct) {
         tmpStruct.push_back(row.get());
     }
     return tmpStruct;
}

void Maze::generateRandomMaze(bool mode) {
    //initialize the maze with walls
     for (int i = 0; i < this->length; i++) {
         for (int j = 0; j < this->width; j++) {
             this->mazeStruct[i][j] = 'x';
         }
     }

     int x_start = 0;
     int z_start = 0;

   if (mode == TESTING_MODE) {
     x_start = 1;
     z_start = 1;
     //entrance/exit
     this->mazeStruct[x_start][z_start - 1] = '.';
     } 
      else {
      //special case for 1x1 maze
        if (this->length == 1 && this->width == 1) {
         this->mazeStruct[0][0] = (rand() % 2) ? '.' : 'x';
         return;
     }
     if (this->length > 2) {
     x_start = 2 * (rand() % ((this->length - 2) / 2 + 1)) + 1;
     }
     if (this->width > 2) {
     z_start = 2 * (rand() % ((this->width - 2) / 2 + 1)) + 1;
     }
     //create the entrance based on random side selection
     bool entranceCreated = false;
     while (!entranceCreated) {
         int side = rand() % 4;

         if (side == 0 && z_start > 0) {
             this->mazeStruct[0][z_start] = '.';
             entranceCreated = true;
         } 
         else if (side == 1 && x_start < this->length - 1) {
             this->mazeStruct[x_start][this->width - 1] = '.';
             entranceCreated = true;
         } 
         else if (side == 2 && z_start < this->width - 1) {
             this->mazeStruct[this->length - 1][z_start] = '.';
             entranceCreated = true;
         } 
         else if (side == 3 && x_start > 0) { 
             this->mazeStruct[x_start][0] = '.';
             entranceCreated = true;
        }
    }
}
     //start the recursive maze generation
     recursiveAlgorithm(x_start, z_start);
}



void Maze::generateRandomMazeEnhanced(bool mode) {
    //initialize the maze with walls
    int bestHeight;
    int nextHeight;
    // mcpp::Coordinate thisCoordTrue = *(this->getStart());
    // int bestHeightTrue = abs(mc.getHeight(thisCoordTrue.x, thisCoordTrue.z));

     for (int i = 0; i < this->length; i++) {
         for (int j = 0; j < this->width; j++) {
            int jp = j + 1;
            mcpp::Coordinate thisCoord = *(this->getStart()) + mcpp::Coordinate(i, 0, j);
            bestHeight = abs(mc.getHeight(thisCoord.x, thisCoord.z));

            if (jp < this->width) {
             nextHeight = abs(mc.getHeight(thisCoord.x, thisCoord.z + 1));
            } else if (jp >= this->width) {
                nextHeight = abs(mc.getHeight(thisCoord.x, thisCoord.z - 1));
            }
            
            int trueDifference = abs(bestHeight - nextHeight);

            


            if (trueDifference < 5) {
                this->mazeStruct[i][j] = 'x';
            } else {
                this->mazeStruct[i][j] = 'o';
            }

         }
     }




     int x_start = 0;
     int z_start = 0;

   if (mode == TESTING_MODE) {
     x_start = 1;
     z_start = 1;
     //entrance/exit
     this->mazeStruct[x_start][z_start - 1] = '.';
     } 
      else {
      //special case for 1x1 maze
        if (this->length == 1 && this->width == 1) {
         this->mazeStruct[0][0] = (rand() % 2) ? '.' : 'x';
         return;
     }
     if (this->length > 2) {
     x_start = 2 * (rand() % ((this->length - 2) / 2 + 1)) + 1;
     }
     if (this->width > 2) {
     z_start = 2 * (rand() % ((this->width - 2) / 2 + 1)) + 1;
     }
     //create the entrance based on random side selection
     bool entranceCreated = false;
     while (!entranceCreated) {
         int side = rand() % 4;

         if (side == 0 && z_start > 0) {
             this->mazeStruct[0][z_start] = '.';
             entranceCreated = true;
         } 
         else if (side == 1 && x_start < this->length - 1) {
             this->mazeStruct[x_start][this->width - 1] = '.';
             entranceCreated = true;
         } 
         else if (side == 2 && z_start < this->width - 1) {
             this->mazeStruct[this->length - 1][z_start] = '.';
             entranceCreated = true;
         } 
         else if (side == 3 && x_start > 0) { 
             this->mazeStruct[x_start][0] = '.';
             entranceCreated = true;
        }
    }
}
     //start the recursive maze generation
     recursiveAlgorithmEnhanced(x_start, z_start);
}




bool Maze::is_valid_move(int x, int z) {
//checks to see if move is valid by seeing if it has visited the cell or not 
return x > 0 && x < length - 1 && z > 0 && z < width - 1 && 
mazeStruct[x][z] == 'x';
}

 bool Maze::enhanced_is_valid_move(int curr_x, int curr_z, int next_x, int next_z)
 {

   mcpp::Coordinate thisCoordNow = *(this->getStart());

    
    bool curr_position_valid = curr_x >= 0 && curr_x < length &&
                               curr_z >= 0 && curr_z < width;

    // Ensure next positions are also within bounds
    bool next_position_valid = next_x >= 0 && next_x < length &&
                               next_z >= 0 && next_z < width;

    // Check the terrain height difference if both current and next positions are valid
    bool height_difference_valid = curr_position_valid && next_position_valid &&
                        abs(abs(mc.getHeight(curr_x + thisCoordNow.x, curr_z + thisCoordNow.z)) - abs(mc.getHeight(next_x + thisCoordNow.x, next_z + thisCoordNow.z))) <= 1;

    // Check if the next position is an unvisited cell ('x') and the height difference is valid
    return curr_position_valid && next_position_valid &&
           mazeStruct[next_x][next_z] == 'x' && height_difference_valid;

 }

std::vector<Maze::Direction> Maze::get_valid(int x, int z) {
     /* 
     * if move is valid, recursive backtracking takes place, 
     * by going back to the previous cell and then looking for other paths
     */
     std::vector<Direction> directions;
     if (is_valid_move(x - 2, z)) {
         directions.push_back(UP);
     }
      if (is_valid_move(x, z + 2)) {
         directions.push_back(RIGHT);
    }
      if (is_valid_move(x + 2, z)) {
         directions.push_back(DOWN);
     }
     if (is_valid_move(x, z - 2)) {
         directions.push_back(LEFT);
     }
    //shuffle directions every time a new maze is generated in normal mode
     if (!this->mode) {
         std::random_device rd;
         std::mt19937 random(rd());
         std::shuffle(directions.begin(), directions.end(), random);
     }
     return directions;
}


std::vector<Maze::Direction> Maze::get_valid_enhanced(int x, int z) {
     /* 
     * if move is valid, recursive backtracking takes place, 
     * by going back to the previous cell and then looking for other paths
*/

    
     std::vector<Direction> directions;
     if (enhanced_is_valid_move(x, z, x - 2, z)) {
         directions.push_back(UP);
     }
      if (enhanced_is_valid_move(x, z, x, z + 2)) {
         directions.push_back(RIGHT);
    }
      if (enhanced_is_valid_move(x, z, x + 2, z)) {
         directions.push_back(DOWN);
     }
     if (enhanced_is_valid_move(x, z, x, z - 2)) {
         directions.push_back(LEFT);
     }
     
    //shuffle directions every time a new maze is generated in normal mode
     if (!this->mode) {
         std::random_device rd;
         std::mt19937 random(rd());
         std::shuffle(directions.begin(), directions.end(), random);
     }
     return directions;
}

void Maze::recursiveAlgorithm(int x, int z) {
    /* 
    * marks a cell as visited then finds all valid directions 
    * from the current cell that is able to be visited 
    */
     mazeStruct[x][z] = '.';
     std::vector<Direction> directions = get_valid(x, z);
     for (Direction direction : directions) {
         int new_x = x, new_z = z;
         if (direction == UP) {
              new_x -= 2;
         } else if (direction == RIGHT) {
             new_z += 2;
         } else if (direction == DOWN) {
             new_x += 2;
         } else if (direction == LEFT) {
            new_z -= 2;
        }

         if (is_valid_move(new_x, new_z)) {
             //carve the path in-between
             mazeStruct[(x + new_x) / 2][(z + new_z) / 2] = '.';
             recursiveAlgorithm(new_x, new_z);
          }
    }
}

bool Maze::one_block(Direction direction, int x, int z) {
     //used for testing mode
     int difference = 0;
      if (direction == UP) {
         difference = loadTerrain[x][z] - loadTerrain[x - 2][z];
     } else if (direction == DOWN) {
         difference = loadTerrain[x][z] - loadTerrain[x + 2][z];
     } else if (direction == RIGHT) {
         difference = loadTerrain[x][z] - loadTerrain[x][z + 2];
     } else if (direction == LEFT) {
         difference = loadTerrain[x][z] - loadTerrain[x][z - 2];
     }
     return abs(difference) <= 1;
}



 void Maze::recursiveAlgorithmEnhanced(int x, int z) {
     mazeStruct[x][z] = '.';
     std::vector<Direction> directions = get_valid_enhanced(x, z);
     for(Direction direction : directions) {
         int new_x = x, new_z = z;
         if(direction == UP) {
             new_x -= 2;
         } 
         else if(direction == RIGHT) {
             new_z += 2;
         } 
         else if(direction == DOWN) {
             new_x += 2;
         } 
         else if(direction == LEFT) {
             new_z -= 2;
         }

         

         if(enhanced_is_valid_move(x, z, new_x, new_z) && x < length - 1 && z < width - 1) {
              //carve the path in-between
             mazeStruct[(x + new_x) / 2][(z + new_z) / 2] = '.'; 
             recursiveAlgorithmEnhanced(new_x, new_z);
         }
     }
 }


void Maze::enhancement_environment() {
    // brainstorming function
   // mcpp::Coordinate currentPosition = mc.getPlayerPosition(); Unused
    //bool GreaterThanOne = false; Unused
    std::vector<int> heightDifference;

    /*
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            loadTerrain[i][j] = mc.getHeight(start->x + i, start->z + j);
            
        }
    }

    // need to possibly increment the x,z counters to check in all x and z coordinates if there is more than a 1 block height difference
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            heightDifference.push_back(loadTerrain[i][j] - loadTerrain[i + 1][j + 1]);

        }
    }

    // Do I build around the height difference? For example if there is a pothole do I go around it and complete the maze. Do I change the maze's structure
    // based on these height changes?

    for (int i : heightDifference) {
        
        if (i > 1) {
        
        } else {

        }

    }
    
        
    int currentHeight = mc.getHeight(x, z);
    int upHeight = mc.getHeight(x-2, z);
    int rightHeight = mc.getHeight(x, z+2);
    int downHeight = mc.getHeight(x+2, z);
    int leftHeight = mc.getHeight(x, z-2);

    return x > 0 && x < length - 1 && z > 0 && z < width - 1 &&
           mazeStruct[x][z] == 'x' && 
           abs(currentHeight - upHeight) <= maxHeight && 
           abs(currentHeight - rightHeight) <= maxHeight &&
           abs(currentHeight - downHeight) <= maxHeight && 
           abs(currentHeight - leftHeight) <= maxHeight;



               int bestHeight;
     for (int i = 0; i < this->length; i++) {
        int ip = i + 1;
         for (int j = 0; j < this->width; j++) {
            int jp = j + 1;
            mcpp::Coordinate thisCoord = *(this->getStart()) + mcpp::Coordinate(i, 0, j);
            bestHeight = abs(mc.getHeight(thisCoord.x, thisCoord.z));
            
            if (jp < this->width && ip < this->length) {
                nextHeight = abs(mc.getHeight(thisCoord.x + 1, thisCoord.z + 1));
            } else if (ip < this->width) {
                nextHeight = abs(mc.getHeight(thisCoord.x + 1, thisCoord.z));
            } else if (jp < this->width) {
                
            }


            if (bestHeight <= 1) {
                this->mazeStruct[i][j] = 'x';
            } else {
                this->mazeStruct[i][j] = 'o';
            }
         }
     }






     void buildMazeEnhanced(std::unique_ptr<Maze>& mazeObj) {
    std::cout << "Executing buildMazeEnhanced..." << std::endl;
     mcpp::MinecraftConnection mc;

     mcpp::Coordinate& mazeStart = *(mazeObj->getStart());

     //restore the terrain and old maze structure first
     

     mcpp::Coordinate teleportPlayer = mazeStart + mcpp::Coordinate(0, 20, 0);
     mc.setPlayerPosition(teleportPlayer);

     int mazeLength = mazeObj->getLength();
     int mazeWidth = mazeObj->getWidth();
     std::vector<char*> mazeStruct = mazeObj->getMazeStruct();
     //reserve space for efficiency 
     mazeStruct.reserve(mazeLength);



    */




    


}
