#include "cube.h"

#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <unordered_map>

using namespace std;

enum Moves {right_move, right_prime_move, left_move, left_prime_move, up_move, up_prime_move, down_move,
 down_prime_move, front_move, front_prime_move, back_move, back_prime_move};

const int MAX_DEPTH = 30; 
const int NUM_OF_MOVES = 12;

class Node {
private:
    RubiksCube currentConfiguration;
    string move;
    Node* prev;
    int depth;
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
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
        {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
        {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
        {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
        {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}
    };

    Node() : prev(nullptr), depth(0) {}

    ~Node() {
        if (prev != nullptr) {
            delete prev;
        }
    }

    // just try to make hash function as best as possible 

    size_t hashConfiguration(Node* current) const {

    // initialize a large prime number for better collision resistance
    const size_t prime = 101;  

    // initialize variables to store hash values for different dimensions
    size_t hash1 = 0, hash2 = 0, hash3 = 0;

    // loop through each dimension and color, applying bitwise operations
    for (int i = 0; i < DIMENSION1; i++) {
        for (int j = 0; j < DIMENSION2; j++) {
        for (int k = 0; k < DIMENSION3; k++) {
            // Combine color value with prime and current hash values
            hash1 = (hash1 * prime + current->currentConfiguration(i, j, k).color) % prime;
            hash2 = (hash2 * prime + (current->currentConfiguration(i, j, k).color << 8)) % prime;  // Shift by 8 bits
            hash3 = (hash3 * prime + (current->currentConfiguration(i, j, k).color << 16)) % prime; // Shift by 16 bits
        }
        }
    }

    // combine the three hash values for better distribution
    return (hash1 ^ hash2 ^ hash3);
}


    Node* createParent() {
        Node* parent = new Node();
        RubiksCube cube;

        cube.takeInput("scramble_moves.txt");
        parent->currentConfiguration = cube;

        return parent;
    }

    bool isSolved(Node* node) {
        for (int i = 0; i < DIMENSION1; i++) {
            for (int j = 0; j < DIMENSION2; j++) {
                for (int k = 0; k < DIMENSION3; k++) {
                    if (node->currentConfiguration(i, j, k).color != solvedCube[i][j][k]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void applyMoves(Node* node, Moves move) {
        RubiksCube cube = node->currentConfiguration;

        switch (move) {
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

        node->currentConfiguration = cube;
    }

void generateChildNodes(Node* node, int depth, queue<Node*>& nodesQueue, unordered_map<size_t, pair<bool, Node*>>& visitedAndNodes){

    vector<Node*> childNodes;

    for (int move = right_move; move <= back_prime_move; move++){

        Node* child = new Node();
        child -> move = moveNames[move];

        child ->prev = node;
        child -> depth = depth + 1;

        applyMoves(child, static_cast<Moves>(move));

        size_t childHash = hashConfiguration(child);

        if (visitedAndNodes[childHash].first == false){
            visitedAndNodes[childHash].first = true;
            visitedAndNodes[childHash].second = child;
            childNodes.push_back(child);
        }else{ 
        
        // collision has been detected, compare it to the states in the hash functions

        Node* existingNode = visitedAndNodes[childHash].second;

        // compare the confugurations directly
        RubiksCube& existingCube = existingNode -> currentConfiguration;
        RubiksCube& newCube = child -> currentConfiguration;

            bool isSame = true;

            // comparing each element of the existing configuration with the new configuration
            
            for (int i = 0; i < DIMENSION1; i++) {
                for (int j = 0; j < DIMENSION2; j++) {
                    for (int k = 0; k < DIMENSION3; k++) {

                        // if any color doesn't match between the existing and new configurations, set isSame to false
                        if (existingCube(i, j, k).color != newCube(i, j, k).color) {
                            isSame = false;
                            break;
                        }
                    }

                    if (!isSame) break;
                }
                if (!isSame) break;
            }

            if (!isSame) {
                // delete the duplicate node from memory
                delete child;
            }
            // if configurations are the same or different, skip generating the node
        }
    }

    // add child nodes to queue

    for (Node* child : childNodes) {
        nodesQueue.push(child);
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

    void backwards_search(Node* node, int depth) {
        Node* current = node;
        stack<string> myMoves;

        while (depth != 0 && current != nullptr) {
            myMoves.push(current->move);
            current = current->prev;
            depth--;

            if (current == nullptr && depth != 0) {
                cout << "Error: Unable to backtrack moves." << endl;
                return;
            }

            if (current != nullptr && isSolved(current)) {
                cout << "Cube is already solved!" << endl;
                return;
            }
        }

        printStack(myMoves);
    }

void ID_BFS() {
    Node* start = createParent();
    start->depth = 0;



    queue<Node*> nodesQueue;

    unordered_map<size_t, pair<bool, Node*>> visitedAndNodes; // Corrected type

    visitedAndNodes[hashConfiguration(start)].first = true; // Initialize with start node
    visitedAndNodes[hashConfiguration(start)].second = start; // Initialize with start node
    nodesQueue.push(start);

    for (int depth = 0; depth <= MAX_DEPTH; depth++) {
        int levelSize = nodesQueue.size();

        for (int i = 0; i < levelSize; i++) {
            Node* current = nodesQueue.front();
            nodesQueue.pop();

            if (isSolved(current)) {
                cout << "Solution found!" << endl;
                backwards_search(current, current->depth);
                return;
            }

            generateChildNodes(current, current->depth, nodesQueue, visitedAndNodes); // pass visitedAndNodes
        }
    }
    throw runtime_error("Solution not found within the depth limit");
}
};

int main() {

    Node node;
    node.ID_BFS();
    return 0;
}