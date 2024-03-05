#include "cube.h"
#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

enum Moves {right_move, right_prime_move, left_move, left_prime_move, up_move, up_prime_move, down_move,
 down_prime_move, front_move, front_prime_move, back_move, back_prime_move};

const int MAX_DEPTH = 30; // eventually work to 20 moves or less (optimize algo)
const int NUM_OF_MOVES = 12;

class Node {
private:


    RubiksCube currentConfiguration;

    // this is where we hold the info ont the move, to access when we bfs 
    string move;

    // pointers to node before so we can traverse the tree once we get to solved state
    Node* prev;

public:

    // array to hold all the moves
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

    // solved cube, just to note, the enums are ints, that
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

    Node() : prev(nullptr) {}

    Node* createParent() {

        Node* parent = new Node();
        RubiksCube cube;

        cube.takeInput();
        parent -> currentConfiguration = cube;

        return parent;
    }

    // this function checks the current configuration
    bool isSolved(Node* node) {
        
        for (int i = 0; i < DIMENSION1; i++) {
            for (int j = 0; j < DIMENSION2; j++) {
                for (int k = 0; k < DIMENSION3; k++) {
                    // remember you did operator overloading, and then access color attribute for cube piece object
                    if (node->currentConfiguration(i, j, k).color != solvedCube[i][j][k]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void applyMoves(Node* node, Moves move) {

        RubiksCube cube = node -> currentConfiguration;

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
                cube.down_prime(); break;
            case front_move:
                cube.front(); break;
            case front_prime_move:
                cube.front_prime(); break;
            case back_move:
                cube.back(); break;
            case back_prime_move:
                cube.back_prime(); break;
        }

        // after transposition is made, set it equal back to cube
        node->currentConfiguration = cube;
    }

    void generateChildNodes(Node* node){

        // this for loop will add 12 child nodes for each node that is put through parameter
        for (int move = right_move; move <= back_prime_move; move++) {

            Node* child = new Node();
            
            child -> move = moveNames[move]; // this attribute for object node holds which move was done to the cube config
            child -> prev = node; // here we are linking the child nodes to the 

            applyMoves(child, static_cast<Moves>(move));

        }
    }


void printStack(stack<string> myStack) {
    cout << "These are the moves to solve the cube: " << endl;
    int move = 1;
    while (!myStack.empty()) {
        cout << "Move " << move << " is " << myStack.top() << '.' << endl;
        myStack.pop();
        move++;
    }
}

    void backwards_search(Node* node, int depth){

        Node* current = node;
        stack<string> myMoves;

        while(depth != 0){
            
        myMoves.push(node -> move);

        current = current -> prev;
        depth--;
            
        }

        // after we have appended everything to the stack, call print stack function
        printStack(myMoves);


    }


    void ID_BFS(){

        // create the parent node by calling function, this is the starting point
        Node* start = createParent();
        queue<Node*> nodesQueue;
        // first item is the start node (it holds the pointer, and as we pop, we can access the moves needed)
        nodesQueue.push(start);


        // max depth of 30, the solution should be solved within then
        for (int depth = 0; depth <= MAX_DEPTH; depth++) {

            int levelSize = nodesQueue.size();

            // we will use a queue to hold all the current nodes at that node and iterate through them 
            // we need to first check if it solved, and if it is not, create the child nodes for that respective 

            for (int i = 0; i < levelSize; i++) {
                Node* current = nodesQueue.front();
                nodesQueue.pop();

                // this is where we check each node and see if it is solved
                if (isSolved(current)) {
                    // run the backwards serch alorithm, print the stack and return
                    backwards_search(current, depth); 
                    return;
                }
                
                // so if it is not solved, then we can generate child nodes for that node
                generateChildNodes(current);

                for (int move = right_move; move <= back_prime_move; move++) {

                    Node* child = new Node();

                    child -> move = moveNames[move];
                    child -> prev = current;

                    applyMoves(child, static_cast<Moves>(move));
                    nodesQueue.push(child);
                }
            }
        }
        // solution not found within the depth limit
        // handle accordingly
    }
};

int main() {
    return 0;
}
