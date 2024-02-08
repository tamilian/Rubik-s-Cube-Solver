#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>     /* srand, rand */

// each term in the enumeration is given a number, which can be used to access in index of array 

enum Color {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW};

using namespace std;

class RubiksCube {
private:
    // dimensions of dynamic 3d vectors holding cube data
    const int DIMENSION1 = 6;
    const int DIMENSION2 = 3;
    const int DIMENSION3 = 3;

    vector<vector<vector<int>>> cube; // 3D vector for cube data

public:
    // Constructor
    RubiksCube() {
        // Resize the 3D vector to the appropriate dimensions
        cube.resize(DIMENSION1, vector<vector<int>>(DIMENSION2, vector<int>(DIMENSION3)));
    }

    // subscript operator overload for accessing cube data
    vector<vector<int>>& operator[](size_t index) {
        if (index >= cube.size()) {
            throw out_of_range("Index out of range!");
        }
        return cube[index];
    }

    

    // Function to read input from a file into the cube vector
    void takeInput() {
        ifstream inputFile("input.txt");

        if (!inputFile.is_open()) {
            cerr << "Failed to open file" << endl;
            return;
        } else {
            // Loop through the dimensions of the cube and read values from the file
            for (int i = 0; i < DIMENSION1; i++) {
                for (int j = 0; j < DIMENSION2; j++) {
                    for (int k = 0; k < DIMENSION3; k++) {
                        int value;
                        if (!(inputFile >> value)) {
                            cerr << "Error reading values from the file." << endl;
                            inputFile.close();
                            return;
                        }
                        cube[i][j][k] = value;
                    }
                }
            }
            // Close the file
            inputFile.close();
        }
    }


    // Function to print the cube for debugging
    void printCube() {
        for (int i = 0; i < DIMENSION1; i++) {
            for (int j = 0; j < DIMENSION2; j++) {
                for (int k = 0; k < DIMENSION3; k++) {
                    cout << cube[i][j][k] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    void scrambleCube(vector<vector<vector<int>>>& cube){

        // starts from the starting cube and gives you a scrambled cube, and puts it into txt file\
        // honestly this is for testing purposes 
    }

    // now we need to come up as many moves as possible and how the transpose 
    // all the moves are with respective to the green center piece

    // MOVES


    // index map of app pieces to help with writing transpositin functions 

/*
            
    rubiksCube[0][0][0] = W   rubiksCube[0][0][1] = W   rubiksCube[0][0][2] = W
    rubiksCube[0][1][0] = W   rubiksCube[0][1][1] = W   rubiksCube[0][1][2] = W
    rubiksCube[0][2][0] = W   rubiksCube[0][2][1] = W   rubiksCube[0][2][2] = W

    rubiksCube[1][0][0] = G   rubiksCube[1][0][1] = G   rubiksCube[1][0][2] = G
    rubiksCube[1][1][0] = G   rubiksCube[1][1][1] = G   rubiksCube[1][1][2] = G
    rubiksCube[1][2][0] = G   rubiksCube[1][2][1] = G   rubiksCube[1][2][2] = G

    rubiksCube[2][0][0] = R   rubiksCube[2][0][1] = R   rubiksCube[2][0][2] = R
    rubiksCube[2][1][0] = R   rubiksCube[2][1][1] = R   rubiksCube[2][1][2] = R
    rubiksCube[2][2][0] = R   rubiksCube[2][2][1] = R   rubiksCube[2][2][2] = R

    rubiksCube[3][0][0] = B   rubiksCube[3][0][1] = B   rubiksCube[3][0][2] = B
    rubiksCube[3][1][0] = B   rubiksCube[3][1][1] = B   rubiksCube[3][1][2] = B
    rubiksCube[3][2][0] = B   rubiksCube[3][2][1] = B   rubiksCube[3][2][2] = B

    rubiksCube[4][0][0] = O   rubiksCube[4][0][1] = O   rubiksCube[4][0][2] = O
    rubiksCube[4][1][0] = O   rubiksCube[4][1][1] = O   rubiksCube[4][1][2] = O
    rubiksCube[4][2][0] = O   rubiksCube[4][2][1] = O   rubiksCube[4][2][2] = O

    rubiksCube[5][0][0] = Y   rubiksCube[5][0][1] = Y   rubiksCube[5][0][2] = Y
    rubiksCube[5][1][0] = Y   rubiksCube[5][1][1] = Y   rubiksCube[5][1][2] = Y
    rubiksCube[5][2][0] = Y   rubiksCube[5][2][1] = Y   rubiksCube[5][2][2] = Y
        
        */

    void rotateFace(vector<vector<vector<int>>>& cube, Color color1Start,Color color1Dest, Color color2Start, Color color2Dest, Color color3Start, 
                    Color color3Dest, Color color4Start, Color color4Dest, Color color5, bool clockwise){
 
        // copy old cube onto new cube
        vector<vector<vector<int>>> temp(cube); // Create a temporary cube


        // the pattern is that the color is the only thing that changes

        // O(a * b * c * d * e), no O(n)


        // the first part is for the roatation itself

        // only j is being incremented


        
        for (int j = 0; j < DIMENSION2; j++) {

            temp[color1Dest][j] = cube[color1Start][j];

            j++;
        }

        for (int j = 0; j < DIMENSION2; j++) {

            temp[color2Dest][j] = cube[color2Start][j];

            j++;
        }


        for (int j = 0; j < DIMENSION2; j++) {

            temp[color3Dest][j] = cube[color3Start][j];

            j++;
        }

        for (int j = 0; j < DIMENSION2; j++) {

            temp[color4Dest][j] = cube[color4Start][j];

            j++;
        }

        // the second part does the same face transposition
        // you cant really loop this as there is no pattern, let's just change it manually

        // it just checks if it is clockwise or not, which is taken in as a parameter

    // rotate the specified face either clockwise or counterclockwise
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
    cube = temp;

    }


    // Right move function ( in respect to green face)
    void right() {

        rotateFace(cube, GREEN, WHITE, WHITE, BLUE ,BLUE, YELLOW, YELLOW, GREEN, RED, true);

    }

    void right_prime(){
                
        rotateFace(cube, WHITE, GREEN, GREEN, YELLOW, YELLOW, BLUE, BLUE, WHITE, RED, false);

    }
    void left(){
        
        rotateFace(cube, WHITE, GREEN, GREEN, YELLOW, YELLOW,BLUE, BLUE, WHITE, ORANGE, true);
    }

    void left_prime(){

        rotateFace(cube, WHITE,BLUE, BLUE, YELLOW, YELLOW, GREEN, GREEN , WHITE, ORANGE, false);

    }

    void up(){

        rotateFace(cube, GREEN, ORANGE, ORANGE, BLUE, BLUE, RED, RED, GREEN, WHITE, true);


    }

    void up_prime(){

        rotateFace(cube, GREEN,RED, RED, BLUE, BLUE, ORANGE, ORANGE, GREEN, WHITE, false);

    }

    void down(){

        rotateFace(cube, GREEN, RED, RED, BLUE, BLUE, ORANGE, ORANGE, GREEN, YELLOW, true);



    }

    void down_prime(){

        rotateFace(cube, GREEN , ORANGE, ORANGE, BLUE, BLUE, RED, RED, GREEN, YELLOW, false);

        

    }

    void front(){

        rotateFace(cube, WHITE, RED, RED, YELLOW, YELLOW,ORANGE, ORANGE, WHITE, GREEN, true);
        

    }

    void front_prime(){

        rotateFace(cube, WHITE,ORANGE, ORANGE, YELLOW, YELLOW, RED, RED, WHITE, GREEN, false); 

    }

    void back(){

        rotateFace(cube, WHITE ,ORANGE, ORANGE, YELLOW, YELLOW, RED, RED, WHITE, BLUE, true); 

    }

    void back_prime(){

        rotateFace(cube, WHITE,RED, RED, YELLOW, YELLOW, ORANGE, ORANGE, WHITE, BLUE, false);
 
    }
  
};

int main(){

    // test move functions here and print resultant cube
}
