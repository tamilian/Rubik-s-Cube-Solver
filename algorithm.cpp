// A* algorithm with iterative deepening

// iterative deepening with breadth first seartch

// heuristic model is used with Manhattan Distance(read papers on it)

class Node {

    public:
    
    RubiksCube cubeState;
    Node* parent;
    int move;

};