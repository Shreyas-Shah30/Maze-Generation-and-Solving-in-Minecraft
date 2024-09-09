#include <thread> 
#include <vector>
#include <memory> 
#include <tuple> 
#include "buildMaze.h"

//define BlockState
struct BlockState {
    mcpp::Coordinate coord;
    mcpp::BlockType type;
};

std::vector<BlockState> modifiedBlocks;
std::tuple<int, int> largestMazeDimensions = {0, 0};

void flattenTerrain(mcpp::Coordinate& basePoint, int length, int width) {
     mcpp::MinecraftConnection mc;

     /*
     * get the largest maze length and width entered to properly delete 
     * the maze structure and restore the terrain
     */
     std::get<0>(largestMazeDimensions) = std::max(std::get<0>
     (largestMazeDimensions), length);
     std::get<1>(largestMazeDimensions) = std::max(std::get<1>
     (largestMazeDimensions), width);
 
     /*
     * get basePoint block, using -2 since y-coordinate of basePoint
     * entered should be one above the ground
     */
     mcpp::BlockType currLandBlock = mc.getBlock
     (basePoint - mcpp::Coordinate(0, 2, 0));

     //reserve space for maximum possible blocks 
     modifiedBlocks.reserve(length * width * 3); 

for (int i = 0; i < length; i++) {
     for (int j = 0; j < width; j++) {
         int x = basePoint.x + i;
         int z = basePoint.z + j;
         int currentHeight = mc.getHeight(x, z);

     /* 
     * if the current block is above or equal to 
     * the height of basePoint.y, set to AIR
     */
     while (currentHeight >= basePoint.y) {
         mcpp::Coordinate coord(x, currentHeight, z);
         modifiedBlocks.push_back({coord, mc.getBlock(coord)});
         mc.setBlock(coord, mcpp::Blocks::AIR);
         currentHeight--;
     }

     /* 
     * if the current block is below the height of basePoint.y,
     * set to the basePoint block
     */
     while (currentHeight < basePoint.y) {
         mcpp::Coordinate coord(x, currentHeight, z);
         modifiedBlocks.push_back({coord, mc.getBlock(coord)});
         mc.setBlock(coord, currLandBlock);
         currentHeight++;
            }
        } 
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

//define a vector to store added maze structure blocks
std::vector<mcpp::Coordinate> addedMazeBlocks;


void buildMaze(std::unique_ptr<Maze>& mazeObj) {
     mcpp::MinecraftConnection mc;

     mcpp::Coordinate& mazeStart = *(mazeObj->getStart());

     //restore the terrain and old maze structure first
     restoreTerrain(mazeStart);

     mcpp::Coordinate teleportPlayer = mazeStart + mcpp::Coordinate(0, 10, 0);
     mc.setPlayerPosition(teleportPlayer);

     int mazeLength = mazeObj->getLength();
     int mazeWidth = mazeObj->getWidth();
     std::vector<char*> mazeStruct = mazeObj->getMazeStruct();
     //reserve space for efficiency 
     mazeStruct.reserve(mazeLength);

     //flatten the terrain for the new maze
     flattenTerrain(mazeStart, mazeLength, mazeWidth);

     //place the blocks for the maze structure 
   for (int i = 0; i < mazeLength; i++) {
    for (int j = 0; j < mazeWidth; j++) {
         if (mazeStruct[i][j] == 'x') {
         mcpp::Coordinate currentCoord = mazeStart + mcpp::Coordinate(i, 0, j);
     for (int y = 0; y < 3; y++) {
         mc.setBlock(currentCoord + mcpp::Coordinate(0, y, 0)
         , mcpp::Blocks::ACACIA_WOOD_PLANK);
         std::this_thread::sleep_for(std::chrono::milliseconds(50));
         //store the added maze structure blocks in the vector
         addedMazeBlocks.push_back(currentCoord + mcpp::Coordinate(0, y, 0));
                 }
            }
        }
    }
}

std::vector<mcpp::Coordinate> addedMazeBlocksEnhanced;

void buildMazeEnhanced(std::unique_ptr<Maze>& mazeObj) {
     bool check =  false;
    std::cout << "Executing buildMazeEnhanced..." << std::endl;
     mcpp::MinecraftConnection mc;

     mcpp::Coordinate& mazeStart = *(mazeObj->getStart());
     

     //restore the terrain and old maze structure first
     restoreTerrainEnhanced(mazeStart);

     mcpp::Coordinate teleportPlayer = mazeStart + mcpp::Coordinate(0, 20, 0);
     mc.setPlayerPosition(teleportPlayer);

     int mazeLength = mazeObj->getLength();
     int mazeWidth = mazeObj->getWidth();
     std::vector<char*> mazeStruct = mazeObj->getMazeStruct();
     //reserve space for efficiency 
     mazeStruct.reserve(mazeLength);
     /*
    mcpp::Coordinate currentCoordTrue = mazeStart;
    int trueReference = abs(mc.getHeight(currentCoordTrue.x, currentCoordTrue.z));
    */

    //error check for too high shift of elevation
for (int i = 0; i < mazeLength; i++) {
    for (int j = 0; j < mazeWidth; j++) {
        if (mazeStruct[i][j] == 'o') {
            check = true;
        }

    }
}


if (check == false) {
    for (int i = 0; i < mazeLength; i++) {
    for (int j = 0; j < mazeWidth; j++) {
         // int jp = j + 1;
         if (mazeStruct[i][j] == 'x') {
            
        /*
         mcpp::Coordinate currentCoord = mazeStart + mcpp::Coordinate(i, 0, j); 
         int reference = abs(mc.getHeight(currentCoord.x, currentCoord.z));
         int nextHeight;
            if (jp < mazeWidth) {
             nextHeight = abs(mc.getHeight(currentCoord.x, currentCoord.z + 1));
            } else if (jp >= mazeWidth) {
                nextHeight = abs(mc.getHeight(currentCoord.x, currentCoord.z - 1));
            }

                if (trueReference - reference == 0) {
                check = true;
                }




            if (reference - nextHeight >= 0 && check == true) {
            for (int y = 0; y < 3; y++) {
                mc.setBlock(currentCoord + mcpp::Coordinate(0, y, 0)
                , mcpp::Blocks::ACACIA_WOOD_PLANK);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //store the added maze structure blocks in the vector
                addedMazeBlocksEnhanced.push_back(currentCoord + mcpp::Coordinate(0, y, 0));
                 }
            } else {
            for (int y = 1; y < 4; y++) {
                mc.setBlock(currentCoord + mcpp::Coordinate(0, y, 0)
                , mcpp::Blocks::ACACIA_WOOD_PLANK);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //store the added maze structure blocks in the vector
                addedMazeBlocksEnhanced.push_back(currentCoord + mcpp::Coordinate(0, y, 0));
                 }
            }


            check = false; 
            */
        mcpp::Coordinate currentCoord = mazeStart + mcpp::Coordinate(i, 0, j); 
         int reference = mc.getHeight(currentCoord.x, currentCoord.z);
         

         currentCoord.y = reference;

         std::cout << "Coordinate: (" << currentCoord.x << ", " << currentCoord.z << "), Height: " << reference << std::endl;

         for (int y = 1; y < 8; y++) {
                mc.setBlock(currentCoord + mcpp::Coordinate(0, y, 0)
                , mcpp::Blocks::ACACIA_WOOD_PLANK);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //store the added maze structure blocks in the vector
                addedMazeBlocksEnhanced.push_back(currentCoord + mcpp::Coordinate(0, y, 0));
                 }
        }
    }
}
} else {
    std::cout << "Elevation difference is too steep to build a maze" << std::endl;
}
}






void restoreTerrain(mcpp::Coordinate& basePoint) {
     mcpp::MinecraftConnection mc;
     //delete the added maze structure blocks
     for (const auto& coord : addedMazeBlocks) {
         mc.setBlock(coord, mcpp::Blocks::AIR);
         std::this_thread::sleep_for(std::chrono::milliseconds(50));
     }

     addedMazeBlocks.clear();
    
     //after maze structure is deleted, restore the original terrain
     for (const auto& blocks : modifiedBlocks) {
         mc.setBlock(blocks.coord, blocks.type);
         std::this_thread::sleep_for(std::chrono::milliseconds(50));
     }

     modifiedBlocks.clear();
}

void restoreTerrainEnhanced(mcpp::Coordinate& basePoint) {
     mcpp::MinecraftConnection mc;
     //delete the added maze structure blocks
     for (const auto& coord : addedMazeBlocksEnhanced) {
         mc.setBlock(coord, mcpp::Blocks::AIR);
         std::this_thread::sleep_for(std::chrono::milliseconds(50));
     }

     addedMazeBlocksEnhanced.clear();

}