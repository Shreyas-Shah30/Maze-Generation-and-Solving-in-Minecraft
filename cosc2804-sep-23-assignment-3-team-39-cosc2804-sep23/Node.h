#include <mcpp/mcpp.h>
#include <vector>

class Node{
    public:
        Node(mcpp::Coordinate incoming, Node* previousNode = nullptr){
            this->coord = incoming;
            this->previousNode = previousNode;
        }
        mcpp::Coordinate coord;
        Node* previousNode = nullptr;

    private:
};