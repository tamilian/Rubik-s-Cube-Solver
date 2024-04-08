#include "cube.h" 

#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <unordered_map>


enum Moves : uint8_t {
 right_move = 0b000,
 right_prime_move = 0b001, 
 left_move = 0b0010, 
 left_prime_move = 0b0011,
 up_move = 0b0100, 
 up_prime_move = 0b0101, 
 down_move = 0b0110,
 down_prime_move = 0b0111, 
 front_move = 0b1000, 
 front_prime_move = 0b1001, 
 back_move = 0b1010, 
 back_prime_move = 0b1011
 };

// maximum depth for search
const int MAX_DEPTH = 30;

// number of possible moves
const int NUM_OF_MOVES = 12; 

class Node {
private:
    RubiksCube currentConfiguration; // current Rubik's Cube configuration
    uint32_t moves; // move made to reach this configuration
    Node* prev; // pointer to previous node in the search tree (for backwards search)
    int depth; // depth of the current node in the search tree
public:

    std::string moveNames[NUM_OF_MOVES] = { // names of possible moves (all respect to green face)
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

    int solvedCube[6][3][3] = { // solved Rubik's Cube configuration
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
        {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
        {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}},
        {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}},
        {{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}
    };

    Node() : prev(nullptr), depth(0) {} 

    ~Node() { // Destructor
        if (prev != nullptr) {
            delete prev;
        }
    }

    //fFunction to hash the Rubik's Cube configuration
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

    // function to create the parent node
    Node* createParent() {
        Node* parent = new Node();
        RubiksCube cube;

        cube.takeInput("scramble_moves.txt"); // generated with scramble function in cube.cpp
        parent->currentConfiguration = cube;

        return parent;
    }

    // function to check if the cube is solved
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

    // function to apply moves to the Rubik's Cube
    void applyMoves(Node* node, Moves move) {
        RubiksCube cube = node->currentConfiguration;

        switch (move) {
            // apply respective move to the cube
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

    // function to generate child nodes from the current node
    
    void generateChildNodes(Node* node, int depth, std::queue<Node*>& nodesQueue,
     std::unordered_map<size_t, std::pair<bool, Node*>>& visitedAndNodes){

        std::vector<Node*> childNodes;

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
                // collision detected
                Node* existingNode = visitedAndNodes[childHash].second;

                // compare the configurations directly
                RubiksCube& existingCube = existingNode -> currentConfiguration;
                RubiksCube& newCube = child -> currentConfiguration;

                bool isSame = true;

                // compare each element of the existing configuration with the new configuration
                for (int i = 0; i < DIMENSION1; i++) {
                    for (int j = 0; j < DIMENSION2; j++) {
                        for (int k = 0; k < DIMENSION3; k++) {
                            // If any color doesn't match between the existing and new configurations, set isSame to false
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
            }
        }

        // add child nodes to queue
        for (Node* child : childNodes) {
            nodesQueue.push(child);
        }
    }

    void printMoves(){
        for (int i = 0; i < depth; i++){
            uint8_t moveIndex = (moves >> (i * 4)) & 0xF; // Extracting 4 bits representing each move
            std::cout << moveNames[moveIndex] << std::endl;
        }
    }


    // function implementing Iterative Deepening Breadth-First Search
    void ID_BFS() {
        Node* start = createParent(); // create the parent node
        start->depth = 0;

        std::queue<Node*> nodesQueue; // queue for BFS traversal

        std::unordered_map<size_t, std::pair<bool, Node*>> visitedAndNodes; // hash table to store visited nodes

        visitedAndNodes[hashConfiguration(start)].first = true; // initialize with start node
        visitedAndNodes[hashConfiguration(start)].second = start; 

        nodesQueue.push(start);

        for (int depth = 0; depth <= MAX_DEPTH; depth++) { // perform iterative deepening

            int levelSize = nodesQueue.size();

            for (int i = 0; i < levelSize; i++) {
                Node* current = nodesQueue.front();
                nodesQueue.pop();

                if (isSolved(current)) { // check if current node is the solution
                    std::cout << "Solution found!" << std::endl;
                    backwards_search(current, current->depth); // print the solution
                    return;
                }

                generateChildNodes(current, current->depth, nodesQueue, visitedAndNodes); // generate child nodes
            }
        }
        throw std::runtime_error("Solution not found within the depth limit!");
    }
};

int main() {

    Node node;
    node.ID_BFS(); // Perform ID-BFS
    return 0;
}
