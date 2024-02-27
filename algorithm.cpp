#include "cube.h"


#include <iostream>
#include <stack>
#include <cstring>

const int MAX_DEPTH = 30;


// A* algorithm with iterative deepening

// iterative deepening with breadth first seartch

// heuristic model is used with Manhattan Distance(read papers on it)

class Node {

    private: 
    
    Node* rightChild;
    Node* rightPrimeChild;
    Node* leftChild;
    Node* leftPrimeChild;
    Node* upChild;
    Node* upPrimeChild;
    Node* downChild;
    Node* downPrimeChild;
    Node* frontChild;
    Node* frontPrimeChild;
    Node* backChild;
    Node* backPrimeChild;

    public:
    





};

// here is a function to check if the rubiks cube is solved
bool isSolved();

void printStack();


