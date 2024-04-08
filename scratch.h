#ifndef SCRATCH_H
#define SCRATCH_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <map>
#include <tuple>
#include <array>

// enum for representing different colors of the cube (3 bits per color)
enum Color : uint8_t {
    WHITE  = 0b000,
    ORANGE = 0b001,
    GREEN  = 0b010,
    RED    = 0b011,
    BLUE   = 0b100,
    YELLOW = 0b101
};
// overloading stream insertion operator to print Color enum
std::ostream& operator<<(std::ostream& os, const Color& color);

// constants for cube dimensions
const int DIMENSION1 = 6;
const int DIMENSION2 = 3;
const int DIMENSION3 = 3;

const int TOTAL_PIECES = 54;

// class representing a single piece of the Rubik's Cube
class CubePiece {
public:
    // color of the piece
    Color color;

    // Original coordinates of the piece
    std::tuple<int, int, int> originalCoordinates;
    
    // current coordinates of the piece (mutable as it will change during rotations)
    mutable std::tuple<int, int, int> currentCoordinates;

    // constructors
    CubePiece();
    
    CubePiece(Color c, int x, int y, int z);

    // assignment operator
    CubePiece& operator=(const CubePiece& other);
};

// class representing the Rubik's Cube
class RubiksCube {
private:

    // 3D array representing the Rubik's Cube
    std::array<CubePiece, TOTAL_PIECES> cube;

public:

    // constructor
    RubiksCube();

    // operator to access cube pieces by coordinates
    CubePiece& operator()(int i, int j, int k);

    bool operator!=(const RubiksCube& other) const;

    // method to take input from a file to initialize the cube
    void takeInput(const std::string& filename);

    // methods for retrieving original and current coordinates of a piece
    void originalCoordinateRetrieval(int x, int y, int z);
    void currentCoordinateRetrieval(int x, int y, int z);

    // method to print original and current coordinates of all pieces in the cube
    void printOriginalAndCurrentCoordinates(RubiksCube &c);

    // method to print the current state of the cube
    void printCube() const;

    void helperFunction(int i, int j, int k);

    // methods to perform rotations on the cube
    void rotateFaceVertical(
    Color color1Start, Color color1Dest, int color1KStart, int color1KEnd,

    Color color2Start, Color color2Dest, int color2KStart, int color2KEnd,

    Color color3Start, Color color3Dest, int color3KStart, int color3KEnd,

    Color color4Start, Color color4Dest, int color4KStart, int color4KEnd,

    Color color5, bool clockwise);


    void rotateFaceHorizontal(

        Color color1Start,  Color color1Dest, 
        
        Color color2Start, Color color2Dest,  
        
        Color color3Start, Color color3Dest, 
        
        Color color4Start, Color color4Dest, 

        Color color5, int jValue,  bool clockwise);

    void rotateFront( 
        Color color1Start, Color color1Dest, int color1JStart, int color1KEnd,  

        Color color2Start,Color color2Dest, int color2KStart , int color2JEnd,  

        Color color3Start,Color color3Dest, int color3JStart, int color3JEnd, 

        Color color4Start,Color color4Dest, int color4KStart, int color4JEnd,

        Color color5);

    void rotateBack( 
        Color color1Start, Color color1Dest, int color1JStart, int color1KEnd,  

        Color color2Start,Color color2Dest, int color2KStart , int color2JEnd,  

        Color color3Start,Color color3Dest, int color3JStart, int color3KEnd, 

        Color color4Start,Color color4Dest, int color4KStart, int color4JEnd,

        Color color5);

    void rotateFrontCounterClockwise( 

        Color color1Start, Color color1Dest, int color1JStart , int color1KEnd,  

        Color color2Start,Color color2Dest, int color2KStart, int color2JEnd ,

        Color color3Start,Color color3Dest, int color3JStart , int color3KEnd,

        Color color4Start,Color color4Dest, int color4KStart, int color4JEnd, 

        Color color5);

    void rotateBackCounterClockWise( 

        Color color1Start, Color color1Dest, int color1JStart, int color1KEnd,  

        Color color2Start,Color color2Dest, int color2KStart, int color2JEnd ,

        Color color3Start,Color color3Dest, int color3JStart , int color3KEnd ,

        Color color4Start,Color color4Dest, int color4KStart , int color4JEnd, 

        Color color5);

        void right();

        void right_prime();

        void left();

        void left_prime();

        void up();

        void up_prime();

        void down();

        void down_prime();

        void front();

        void back();

        void front_prime();

        void back_prime();

    // method to scramble the cube
        void scramble(int numMoves);

};

#endif // SCRATCH_H
