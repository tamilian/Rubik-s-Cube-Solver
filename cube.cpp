#include <iostream>
#include <fstream>
#include <vector>

// each term in the enumeration is given a number, which can be used to access in index of array 

enum Color {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW};

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

    void rotateFace(Color color1Start,Color color1Dest, Color color2Start, Color color2Dest, Color color3Start, 
                    Color color3Dest, Color color4Dest, Color color4Start, Color color5, Color clockwise){
 
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

        j = 0;

        for (int j = 0; j < DIMENSION2; j++) {

            temp[color3Dest][j] = cube[color3Start][j];

            j++;
        }

        j = 0;

        for (int j = 0; j < DIMENSION2; j++) {

            temp[color4Dest][j] = cube[color4Start][j];

            j++;
        }

        // the second part does the same face transposition
        // you cant really loop this as there is no pattern, let's just change it manually

        // it just checks if it is clockwise or not, which is taken in as a parameter

        if (clockwise){

        temp[color5][0][2] = cube[color5][0][0];
        temp[color5][1][2] = cube[color5][0][1];
        temp[color5][2][2] = cube[color5][0][2];

        temp[color5][0][1] = cube[color5][1][0];
        temp[color5][2][1] = cube[color5][1][2];

        temp[color5][0][0] = cube[color5][2][0];
        temp[color5][1][0] = cube[color5][2][1];
        temp[color5][2][0] = cube[color5][2][2];
            
            

        }
        else{

        temp[color5][2][0] = cube[color5][0][0];
        temp[color5][1][0] = cube[color5][0][1];
        temp[color5][2][0] = cube[color5][0][2];

        temp[color5][2][1] = cube[color5][1][0];
        temp[color5][0][1] = cube[color5][1][2];

        temp[color5][2][2] = cube[color5][2][0];
        temp[color5][1][2] = cube[color5][2][1];
        temp[color5][0][2] = cube[color5][2][2];     

        }

    }


    // Right move function
    void right() {
        vector<vector<vector<int>>> temp(cube); // Create a temporary cube

        // Yellow moves to green center piece
        temp[2][0][2] = cube[5][0][2];
        temp[2][1][2] = cube[5][1][2];
        temp[2][2][2] = cube[5][2][2];

        // Green moves to white
        temp[0][0][2] = cube[2][0][2];
        temp[0][1][2] = cube[2][1][2];
        temp[0][2][2] = cube[2][2][2];

        // White moves to blue
        temp[4][0][2] = cube[0][0][2];
        temp[4][1][2] = cube[0][1][2];
        temp[4][2][2] = cube[0][2][2];

        // Blue moves to yellow
        temp[5][0][2] = cube[4][0][2];
        temp[5][1][2] = cube[4][1][2];
        temp[5][2][2] = cube[4][2][2];

        // Red face transpositions
        temp[3][0][2] = cube[3][0][0];
        temp[3][1][2] = cube[3][0][1];
        temp[3][2][2] = cube[3][0][2];
        temp[3][0][1] = cube[3][1][0];
        temp[3][2][1] = cube[3][1][2];
        temp[3][0][0] = cube[3][2][0];
        temp[3][1][0] = cube[3][2][1];
        temp[3][2][0] = cube[3][2][2];

        // Update the cube with the temporary cube
        cube = temp;
    }

    void right_prime(){
                
                
        vector<vector<vector<int>>> temp(cube); // Create a temporary cube
        
        // white to green 
        temp[2][0][2] = cube[0][0][2];
        temp[2][1][2] = cube[0][1][2];
        temp[2][2][2] = cube[0][2][2];

        // green to yellow
        temp[5][0][2] = cube[2][0][2];
        temp[5][1][2] = cube[2][1][2];
        temp[5][2][2] = cube[2][2][2];
        
        // yellow to blue
        temp[4][0][2] = cube[5][0][2];
        temp[4][1][2] = cube[5][1][2];
        temp[4][2][2] = cube[5][2][2];

        // blue to white 
        temp[0][0][2] = cube[4][0][2];
        temp[0][1][2] = cube[4][1][2];
        temp[0][2][2] = cube[4][2][2];


        temp[3][2][0] = cube[3][0][0];
        temp[3][1][0] = cube[3][0][1];
        temp[3][2][0] = cube[3][0][2];

        temp[3][2][1] = cube[3][1][0];
        temp[3][0][1] = cube[3][1][2];

        temp[3][2][2] = cube[3][2][0];
        temp[3][1][2] = cube[3][2][1];
        temp[3][0][2] = cube[3][2][2];

        cube = temp;

    }


    void left(){
        
        vector<vector<vector<int>>> temp(cube); // Create a temporary cube

        // white to green
        temp[2][0][0] = cube[0][0][0];
        temp[2][1][0] = cube[0][1][0];
        temp[2][2][0] = cube[0][2][0];

        // green to yellow
        temp[5][0][0] = cube[2][0][0];
        temp[5][1][0] = cube[2][1][0];
        temp[5][2][0] = cube[2][2][0];

        // yellow to blue
        temp[4][0][0] = cube[5][0][0];
        temp[4][1][0] = cube[5][1][0];
        temp[4][2][0] = cube[5][2][0];

        // blue to white 
        temp[0][0][0] = cube[4][0][0];
        temp[0][1][0] = cube[4][1][0];
        temp[0][2][0] = cube[4][2][0];





        // top row 
        temp[1][0][2] = cube[1][0][0];
        temp[1][1][2] = cube[1][0][1];
        temp[1][2][2] = cube[1][0][2];

        // middle
        temp[1][0][1] = cube[1][1][0];
        temp[1][1][2] = cube[1][2][1];

        // bottom row 
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    void left_prime(){

    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** up(int*** cube){

    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** up_prime(int*** cube){
        
    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** down(int*** cube){

    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** down_prime(){
        
    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** front(){
        
    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** front_prime(int*** cube){
        
    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** back(int*** cube){
        
    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }

    int*** back_prime(int*** cube){
        
    int*** temp;

    temp = new int **[DIMENSION1];

        for (int i = 0; i < DIMENSION1; i++){

            temp[i] = new int *[DIMENSION2];

            for (int j = 0; j < DIMENSION2; j++){
                temp[i][j] = new int[DIMENSION3];
            
            }
        }

        
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];

        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
        temp[i][j][k] = cube[i][j][k];
    }
  

};






