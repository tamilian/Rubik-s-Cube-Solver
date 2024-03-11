#ifndef CUBE_H
#define CUBE_H

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

    tuple <int, int, int> originalCoordinates;

    mutable tuple<int, int, int> currentCoordinates;

    // Default constructor 
    CubePiece() : color(WHITE), originalCoordinates(make_tuple(0, 0, 0)), currentCoordinates(make_tuple(0, 0, 0)) {}

    // Parameterized constructor
    CubePiece(Color c, int x, int y, int z) : color(c), originalCoordinates(make_tuple(x, y, z)), currentCoordinates(make_tuple(x, y, z)) {}

    // Inside the CubePiece class definition
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
    RubiksCube();

    CubePiece& operator()(int i, int j, int k);

    void takeInput();

    void originalCoordinateRetrieval(int x, int y, int z);

    void currentCoordinateRetrieval(int x, int y, int z);

    void printCube() const;

    void scramble();

    void rotateFaceVertical(Color color1Start, Color color1Dest, 
        Color color2Start, Color color2Dest, 
        Color color3Start, Color color3Dest, 
        Color color4Start, Color color4Dest, 
        Color color5, int kValue, bool clockwise);

    void rotateFaceHorizontal(Color color1Start, 
        Color color1Dest, Color color2Start,
        Color color2Dest,  Color color3Start,
        Color color3Dest, Color color4Start, Color color4Dest, 
        Color color5, int jValue,  bool clockwise);

    void right();

    void right_prime();

    void left();

    void left_prime();

    void up();

    void up_prime();

    void down();

    void down_prime();

    void front();

    void front_prime();

    void back();
    
    void back_prime();

};

#endif // CUBE_H
