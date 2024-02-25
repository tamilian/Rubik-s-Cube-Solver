#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
#include <tuple>
using namespace std;

enum Color {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW};

ostream& operator<<(ostream& os, const Color& color) {
    switch (color) {
        case WHITE: os << "W"; break;
        case ORANGE: os << "O"; break;
        case GREEN: os << "G"; break;
        case RED: os << "R"; break;
        case BLUE: os << "B"; break;
        case YELLOW: os << "Y"; break;
        default: os << "U"; break; // Unknown color
    }
    return os;
}


const int DIMENSION1 = 6;
const int DIMENSION2 = 3;
const int DIMENSION3 = 3;

class CubePiece {
public:

    Color color;

    tuple<int, int, int> originalCoordinates;

    mutable tuple<int, int, int> currentCoordinates;

    // Default constructor 
    CubePiece() : color(WHITE), originalCoordinates(make_tuple(0, 0, 0)), currentCoordinates(make_tuple(0, 0, 0)) {}

    // Parameterized constructor
    CubePiece(Color c, int x, int y, int z) : color(c), originalCoordinates(make_tuple(x, y, z)), currentCoordinates(make_tuple(x, y, z)) {}

    // copy assignment operator 
    CubePiece& operator=(const CubePiece& other) {
        if (this != &other) { // self-assignment check
            color = other.color;
            originalCoordinates = other.originalCoordinates;
            currentCoordinates = other.currentCoordinates;
        }
        return *this;
    }

};

class RubiksCube {
private:
    CubePiece cube[DIMENSION1][DIMENSION2][DIMENSION3];

public: 
    RubiksCube() {

        // initialize the cube with default colors and coordinates
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    cube[i][j][k] = CubePiece(WHITE, i, j, k); // initialize with default color (e.g., WHITE)
                }
            }
        }
    }

    CubePiece& operator()(int i, int j, int k) {
        if (i < 0 || i >= DIMENSION1 || j < 0 || j >= DIMENSION2 || k < 0 || k >= DIMENSION3) {
            throw std::out_of_range("Index out of range!");
        }
        return cube[i][j][k];
    }

void takeInput() {

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file input.txt" << endl;
        return;
    }

    // Initialize the cube with colors from the input file

    int colorIndex;
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                // Read color index from the input file
                inputFile >> colorIndex;

                // Map color index to Color enum
                Color color;
                switch(colorIndex) {
                    case 0: color = WHITE; break;
                    case 1: color = ORANGE; break;
                    case 2: color = GREEN; break;
                    case 3: color = RED; break;
                    case 4: color = BLUE; break;
                    case 5: color = YELLOW; break;
                    default:
                        cerr << "Error: Invalid color index in input file." << endl;
                        return;
                }

                // Set color for the cube piece
                // basically this is a 3d array with
                cube[i][j][k] = CubePiece(color, i, j, k);
            }
        }
    }

    inputFile.close();
}

void originalCoordinateRetrieval(int x, int y, int z){

    // check if input is within bounds

    if (x < 0 || x >= DIMENSION1 || y < 0 || y >= DIMENSION2 || z < 0 || z >= DIMENSION3){
        cerr << "Your dimensions are out of bounds" << endl;
    }

    tuple<int, int, int> originalCords = cube[x][y][z].originalCoordinates;

    // use get method in tuple to access each original coordinate

    cout << "Original Coordinates of this piece at (" << x << ", " << y <<  ", " << z <<  ") "
        << " are " << endl << 
        "(" << get<0>(originalCords) << ", " << get<1>(originalCords) << ", " << get<2>(originalCords) << "). " << endl;

}



void printCube() const {
    for (int i = 0; i < DIMENSION1; i++) {
        for (int j = 0; j < DIMENSION2; j++) {
            for (int k = 0; k < DIMENSION3; k++) {
                std::cout << cube[i][j][k].color << " "; // assuming Color enum has a proper stream insertion operator
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}  

/*
    // all the moves are with respective to the green center piece

 
    void rotateFaceVertical(int (&cube)[DIMENSION1][DIMENSION2][DIMENSION3], Color color1Start, 
    Color color1Dest, Color color2Start,
    Color color2Dest,  Color color3Start,
    Color color3Dest, Color color4Start, Color color4Dest, 
      Color color5,int kValue,  bool clockwise){

    
     CubePiece temp[DIMENSION1][DIMENSION2][DIMENSION3]; // Create a temporary CubePiece array

    // Copy cube to temp
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                temp[i][j][k] = cube[i][j][k];
            }
        }
    }

        
        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color1Dest)][j][kValue].currentCoordinates = cube[static_cast<int>(color1Start)][j][kValue].currentCoordinates;
        }

        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color2Dest)][j][kValue] = cube[static_cast<int>(color2Start)][j][kValue];
        }


        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color3Dest)][j][kValue] = cube[static_cast<int>(color3Start)][j][kValue];

        }

        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color4Dest)][j][kValue] = cube[static_cast<int>(color4Start)][j][kValue];

        }

    if (clockwise) {

        // perform clockwise rotation

        // update the positions of the elements on the specified face
        temp[color5][0][2] = cube[color5][0][0];
        temp[color5][1][2] = cube[color5][0][1];
        temp[color5][2][2] = cube[color5][0][2];

        temp[color5][0][1] = cube[color5][1][0];
        temp[color5][2][1] = cube[color5][1][2];

        temp[color5][0][0] = cube[color5][2][0];
        temp[color5][1][0] = cube[color5][2][1];
        temp[color5][2][0] = cube[color5][2][2];
    } else {

        // perform counterclockwise rotation
        // update the positions of the elements on the specified face
        temp[color5][2][0] = cube[color5][0][0];
        temp[color5][1][0] = cube[color5][0][1];
        temp[color5][0][0] = cube[color5][0][2];

        temp[color5][2][1] = cube[color5][1][0];
        temp[color5][0][1] = cube[color5][1][2];

        temp[color5][2][2] = cube[color5][2][0];
        temp[color5][1][2] = cube[color5][2][1];
        temp[color5][0][2] = cube[color5][2][2];
    }

    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
    }

    
    void rotateFaceHorizontal(int (&cube)[DIMENSION1][DIMENSION2][DIMENSION3], Color color1Start, 
    Color color1Dest, Color color2Start,
    Color color2Dest,  Color color3Start,
    Color color3Dest, Color color4Start, Color color4Dest, 
      Color color5,int jValue,  bool clockwise){
 
     int temp[DIMENSION1][DIMENSION2][DIMENSION3];
    // Copy cube to temp
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                temp[i][j][k] = cube[i][j][k];
            }
        }
    }

        
        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color1Dest)][jValue][j] = cube[static_cast<int>(color1Start)][jValue][j];
        }

        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color2Dest)][jValue][j] = cube[static_cast<int>(color2Start)][jValue][j];
        }


        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color3Dest)][jValue][j] = cube[static_cast<int>(color3Start)][jValue][j];

        }

        for (int j = 0; j < 3; j++) {

            temp[static_cast<int>(color4Dest)][jValue][j] = cube[static_cast<int>(color4Start)][jValue][j];

        }

    if (clockwise) {

        // perform clockwise rotation

        // update the positions of the elements on the specified face
        temp[color5][0][2] = cube[color5][0][0];
        temp[color5][1][2] = cube[color5][0][1];
        temp[color5][2][2] = cube[color5][0][2];

        temp[color5][0][1] = cube[color5][1][0];
        temp[color5][2][1] = cube[color5][1][2];

        temp[color5][0][0] = cube[color5][2][0];
        temp[color5][1][0] = cube[color5][2][1];
        temp[color5][2][0] = cube[color5][2][2];
    } else {

        // perform counterclockwise rotation
        // update the positions of the elements on the specified face
        temp[color5][2][0] = cube[color5][0][0];
        temp[color5][1][0] = cube[color5][0][1];
        temp[color5][0][0] = cube[color5][0][2];

        temp[color5][2][1] = cube[color5][1][0];
        temp[color5][0][1] = cube[color5][1][2];

        temp[color5][2][2] = cube[color5][2][0];
        temp[color5][1][2] = cube[color5][2][1];
        temp[color5][0][2] = cube[color5][2][2];
    }

    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
    }

/*
    void rotateFaceSpecialClockwise(int (&cube)[DIMENSION1][DIMENSION2][DIMENSION3],
    Color color1Start, Color color1Dest, int color1JInitial, int color1JFinal,  

    Color color2Start,Color color2Dest, int color2KStart, int color2JEnd,  

    Color color3Start,Color color3Dest, int color3KEnd, int color3Initial, 

    Color color4Start,Color color4Dest, int color4KStart, int color4JEnd,

    Color color5){
 
     int temp[DIMENSION1][DIMENSION2][DIMENSION3];
    // Copy cube to temp
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                temp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // move 1

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color1Dest)][j][color1JFinal] = cube[static_cast<int>(color1Start)][color1JInitial][j];
        }

    // move 2
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color2Dest)][color2JEnd][j] = cube[static_cast<int>(color2Start)][j][color2KStart];
        }

    // move 3

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color3Dest)][j][color3KEnd] = cube[static_cast<int>(color3Start)][color3Initial][j];
        }
    // move 4

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color4Dest)][color4JEnd][j] = cube[static_cast<int>(color4Start)][j][color4KStart];
        }  




        // perform clockwise rotation

        temp[color5][0][2] = cube[color5][0][0];
        temp[color5][1][2] = cube[color5][0][1];
        temp[color5][2][2] = cube[color5][0][2];

        temp[color5][0][1] = cube[color5][1][0];
        temp[color5][2][1] = cube[color5][1][2];

        temp[color5][0][0] = cube[color5][2][0];
        temp[color5][1][0] = cube[color5][2][1];
        temp[color5][2][0] = cube[color5][2][2];

    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
    }

    void rotateFaceSpecialCounterClockWise(int (&cube)[DIMENSION1][DIMENSION2][DIMENSION3],

    Color color1Start, Color color1Dest, int color1KEnd, int color1JStart,  

    Color color2Start,Color color2Dest, int color2JEnd, int color2KStart,

    Color color3Start,Color color3Dest, int color3JStart, int color3KEnd,

    Color color4Start,Color color4Dest, int color4KStart, int color4JStart, 

    Color color5){
 
     int temp[DIMENSION1][DIMENSION2][DIMENSION3];
    // Copy cube to temp
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                temp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // move 1

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color1Dest)][j][color1KEnd] = cube[static_cast<int>(color1Start)][color1JStart][j];
        }

    // move 2
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color2Dest)][color2JEnd][j] = cube[static_cast<int>(color2Start)][j][color2KStart];
        }

    // move 3
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color3Dest)][j][color3KEnd] = cube[static_cast<int>(color3Start)][color3JStart][j];
        }
    // move 4

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color4Dest)][color4JStart][j] = cube[static_cast<int>(color4Start)][j][color4KStart];
        }  


        // perform counterclockwise rotation
        // update the positions of the elements on the specified face
        temp[color5][2][0] = cube[color5][0][0];
        temp[color5][1][0] = cube[color5][0][1];
        temp[color5][0][0] = cube[color5][0][2];

        temp[color5][2][1] = cube[color5][1][0];
        temp[color5][0][1] = cube[color5][1][2];

        temp[color5][2][2] = cube[color5][2][0];
        temp[color5][1][2] = cube[color5][2][1];
        temp[color5][0][2] = cube[color5][2][2];
    

    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
    }
*/

/*

    // Right move function ( in respect to green face)
    void right() { // vertical funciton
        rotateFaceVertical(cube, GREEN, WHITE, WHITE, BLUE ,BLUE, YELLOW, YELLOW, GREEN, RED, 2, true);
    }

    void right_prime(){    // vertical function
        rotateFaceVertical(cube, WHITE, GREEN, GREEN, YELLOW, YELLOW, BLUE, BLUE, WHITE, RED, 2, false);
    }

    void left(){        // vertical function
        rotateFaceVertical(cube, WHITE, GREEN, GREEN, YELLOW, YELLOW,BLUE, BLUE, WHITE, ORANGE, 0, true);
    }

    void left_prime(){  // vertical function
        rotateFaceVertical(cube, WHITE,BLUE, BLUE, YELLOW, YELLOW, GREEN, GREEN , WHITE, ORANGE, 0, false);
    }

    void up(){ // horizontal function
        rotateFaceHorizontal(cube, GREEN, ORANGE, ORANGE, BLUE, BLUE, RED, RED, GREEN, WHITE, 0, true);
    }

    void up_prime(){ // horizontal function
        rotateFaceHorizontal(cube, GREEN,RED, RED, BLUE, BLUE, ORANGE, ORANGE, GREEN, WHITE, 0,  false);
    }

    void down(){ // horizontal function
        rotateFaceHorizontal(cube, GREEN, RED, RED, BLUE, BLUE, ORANGE, ORANGE, GREEN, YELLOW, 2, true);
    }

    void down_prime(){ // horizontal function
        rotateFaceHorizontal(cube, GREEN , ORANGE, ORANGE, BLUE, BLUE, RED, RED, GREEN, YELLOW, 2, false);
    }

    */
/*
    void front(){ // special case
        rotateFaceSpecialClockwise(cube, WHITE, RED, 2, 0,
         RED, YELLOW, 
         YELLOW,ORANGE,
          ORANGE, WHITE, 
          GREEN);
    }

    void front_prime(){ // special case
        rotateFaceSpecialCounterClockWise(cube, WHITE,ORANGE, ORANGE, YELLOW, YELLOW, RED, RED, WHITE, GREEN, false); 
    }

    void back(){ // special case
        rotateFaceSpecialCounterClockwise(cube, WHITE ,ORANGE, ORANGE, YELLOW, YELLOW,
        
         RED, RED, WHITE, BLUE, true); 
    }

    void back_prime(){ // special case
        rotateFaceSpecialCounterClockWise(cube, WHITE,RED, RED, YELLOW, YELLOW, ORANGE, ORANGE, WHITE, BLUE, false);
    }
    */
};

int main(){

    // create a rubiks cube object
    RubiksCube cube;

    cube.takeInput();
    cube.printCube();

    int x = 1, y = 1, z = 1;

    cube.originalCoordinateRetrieval(x,y,z);

    return 0;
}