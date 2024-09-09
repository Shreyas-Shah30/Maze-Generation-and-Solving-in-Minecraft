#include "menuUtils.h"

void printStartText(){
    std::cout << std::endl;
    std::cout << "Welcome to MineCraft MazeRunner!" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

void printMainMenu(){
    std::cout << std::endl;
    std::cout << "------------- MAIN MENU -------------" << std::endl;
    std::cout << "1) Generate Maze" << std::endl;
    std::cout << "2) Build Maze in MineCraft" << std::endl;
    std::cout << "3) Solve Maze" << std::endl;
    std::cout << "4) Enhancements Menu" << std::endl;
    std::cout << "5) Show Team Information" << std::endl;
    std::cout << "6) Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printGenerateMazeMenu(){
    std::cout << std::endl;
    std::cout << "------------- GENERATE MAZE -------------" << std::endl;
    std::cout << "1) Read Maze from terminal" << std::endl;
    std::cout << "2) Generate Random Maze" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printSolveMazeMenu(){
    std::cout << std::endl;
    std::cout << "------------- SOLVE MAZE -------------" << std::endl;
    std::cout << "1) Solve Manually" << std::endl;
    std::cout << "2) Show Escape Route" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}


void printTeamInfo(){
    std::cout << std::endl;
    std::cout << "Team members:" << std::endl;

    std::cout << "\t [1] Shreyas Shah (s4005805@student.rmit.edu.au)"
    << std::endl;
    std::cout << "\t [2] Harrison Orosz (s4007645@student.rmit.edu.au)" 
    << std::endl;
    std::cout << "\t [3] Leo Park (s4007934@student.rmit.edu.au)" 
    << std::endl;
    std::cout << "\t [4] Daniel Lienert (s4007921@student.rmit.edu.au)" 
    << std::endl;

    std::cout << std::endl;
}

void printEnhancements(){
    std::cout << std::endl;
    std::cout << "------------- ENHANCEMENTS -------------" << std::endl;
    std::cout << "1) Create maze without flattening terrain" << std::endl;
    std::cout << "2) Find shortest path to exit in maze" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printExitMassage(){
    std::cout << std::endl;
    std::cout << "The End!" << std::endl;
    std::cout << std::endl;
}