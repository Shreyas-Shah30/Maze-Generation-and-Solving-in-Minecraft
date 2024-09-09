#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>
#include <memory>
#include <random>
#define NORMAL_MODE 0
#define TESTING_MODE 1

class Maze
{

public:
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                        unsigned int zlen,
                                        bool mode);
    int getLength();
    int getWidth(); 
    void setLength(int length);
    void setWidth(int width); 
    void setStart(std::unique_ptr<mcpp::Coordinate> start);
    mcpp::Coordinate* getStart();
    void setMazeStruct(std::vector<std::unique_ptr<char[]>> mazeStructArray);
    std::vector<char*> getMazeStruct();
    void generateRandomMaze(bool mode); 
     void generateRandomMazeEnhanced(bool mode);
    void enhancement_environment(); 
     void recursiveAlgorithmEnhanced(int x, int z);
    

private:
    enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT,
    };
    int length;
    int width;

    bool mode; 
    std::unique_ptr<mcpp::Coordinate> start;
    std::vector<std::unique_ptr<char[]>> mazeStruct;
    mcpp::MinecraftConnection mc;
    std::vector<Direction> get_valid_enhanced(int x, int z);
    std::vector<Direction> get_valid(int x, int z);
    void recursiveAlgorithm(int x, int z);
    std::vector<std::vector<int>> loadTerrain; 
    bool one_block(Direction direction, int x, int z); 
    bool is_valid_move(int x, int z);
    bool enhanced_is_valid_move(int curr_x, int curr_z, int next_x, int next_z);
    
};


#endif //ASSIGN_MAZE_H
