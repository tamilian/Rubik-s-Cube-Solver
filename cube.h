#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <map>
#include <tuple>

enum Color {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW};

std::ostream& operator<<(std::ostream& os, const Color& color);

const int DIMENSION1 = 6;
const int DIMENSION2 = 3;
const int DIMENSION3 = 3;

class CubePiece {
public:
    Color color;
    std::tuple<int, int, int> originalCoordinates;
    mutable std::tuple<int, int, int> currentCoordinates;

    CubePiece();
    CubePiece(Color c, int x, int y, int z);

    CubePiece& operator=(const CubePiece& other);
};

class RubiksCube {
private:
    CubePiece cube[DIMENSION1][DIMENSION2][DIMENSION3];

    public:

    RubiksCube();

    CubePiece& operator()(int i, int j, int k);

    void takeInput(const std::string& filename);

    void originalCoordinateRetrieval(int x, int y, int z);

    void currentCoordinateRetrieval(int x, int y, int z);

    void printOriginalAndCurrentCoordinates(RubiksCube &c);

    void printCube() const;

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

        void scramble();

};

#endif // CUBE_H
