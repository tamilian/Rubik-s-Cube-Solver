#include "cube.h"
#include <iostream>
#include <array>
#include <stack>
#include <cstring>


enum Moves {right_move, right_prime_move, left_move, left_prime_move, up_move, up_prime_move, down_move,
 down_prime_move, front_move, front_prime_move, back_move, back_prime_move};

const int MAX_DEPTH = 30; // eventually work to 20 moves or less (optimize algo)
const int NUM_OF_MOVES = 12;


// roadmap for algorithm
// A* algorithm with iterative deepening
// iterative deepening with breadth first seartch
// heuristic model is used with Manhattan Distance(read papers on it)

class Node {
private:


    RubiksCube currentConfiguration;
    string move;

    Node* prev;
    Node* next;

public:

    string moveNames[NUM_OF_MOVES] = {
        "right", 
        "right_prime", 
        "left", 
        "left_prime", 
        "up", 
        "up_prime", 
        "down",
        "down_prime", 
        "front", 
        "front_prime", 
        "back", 
        "back_prime"
    };


    int solvedCube[6][3][3] = {
        // Up/White
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        // Front/Green
        {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
        // Right/Red
        {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
        // Left/Orange
        {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
        // Down/Yellow
        {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
        // Back/Blue
        {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}
    };

    // Default constructor
    Node() : prev(nullptr), next(nullptr) {}


    bool isSolved(Node* node) {
        for (int i = 0; i < DIMENSION1; i++) {
            for (int j = 0; j < DIMENSION2; j++) {
                for (int k = 0; k < DIMENSION3; k++) {
                    // fix this error 
                    if (node->currentConfiguration[i][j][k] != solvedCube[i][j][k]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void generateChildNodes(Node* node, int depth, Moves move) {
        if (depth == 0) {
            return; // we have reached the maximum depth of 30
        }

        // Implement logic to generate child nodes
        // for each move (e.g., right, left, up, down, front, back), create a new child node
        for (int move = right_move; move <= back_prime_move; ++move) {

            Node* child = new Node();

            // string attribute to hold which move has been acted on it 
            child-> move = moveNames[move];
            child->prev = node;
            
            // Apply the move to the Rubik's cube configuration of the child
        }
    }
};


  void applyMoves(Node* parent, int depth, Moves move){

    RubiksCube cube;

    switch(move){
        case right_move:
        cube.right(); break;
        
        case right_prime_move:
        cube.right_prime(); break;

        case left_move:
        cube.left(); break;

        case left_prime_move:
        cube.left_prime(); break;

        case up_move;
        cube.up_move(); break;

    }
}

