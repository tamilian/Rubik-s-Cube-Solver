#include "cube.h"
#include <iostream>
#include <array>
#include <stack>
#include <cstring>



enum Moves {right_move, right_prime_move, left_move, left_prime_move, up_move, up_prime_move, down_move,
 down_prime_move, front_move, front_prime_move, back_move, back_prime_move};

const int MAX_DEPTH = 30; // eventually work to 20 moves or less (optimize algo)
const int NUM_OF_MOVES = 12;

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

    Node() : prev(nullptr), next(nullptr) {}

    Node* createParent() {
        Node* parent = new Node();
        RubiksCube cube;

        cube.takeInput();

        parent->currentConfiguration = cube;

        return parent;
    }

    bool isSolved(Node* node) {

        for (int i = 0; i < DIMENSION1; i++) {
            for (int j = 0; j < DIMENSION2; j++) {
                for (int k = 0; k < DIMENSION3; k++) {
                    if (node->currentConfiguration(i, j, k) != solvedCube[i][j][k]) {

                        return false;
                    }
                }
            }
        }
        return true;
    }

    void generateChildNodes(Node* node, int depth) {
        if (depth == 0) {
            return; // we have reached the maximum depth of 30
        }

        // Implement logic to generate child nodes
        // for each move (e.g., right, left, up, down, front, back), create a new child node
        for (int move = right_move; move <= back_prime_move; ++move) {
            Node* child = new Node();

            // string attribute to hold which move has been acted on it 
            child->move = moveNames[move];
            child->prev = node;

            applyMoves(child, static_cast<Moves>(move));

            generateChildNodes(child, depth - 1);
        }
    }

    void applyMoves(Node* node, Moves move) {
        RubiksCube cube = node->currentConfiguration;

        switch(move) {

            case right_move:
                cube.right(); break;
            case right_prime_move:
                cube.right_prime(); break;
            case left_move:
                cube.left(); break;
            case left_prime_move:
                cube.left_prime(); break;
            case up_move:
                cube.up(); break;
            case up_prime_move:
                cube.up_prime(); break;
            case down_move:
                cube.down(); break;
            case down_prime_move:
                cube.down_prime();
            case front_move:
                cube.front();
            case front_prime_move:
                cube.front_prime();
            case back_move:
                cube.back();
            case back_prime_move:
                cube.back_prime();
       }

        node->currentConfiguration = cube;
    }
};

int main() {
    // Add your main logic here
    return 0;
}
