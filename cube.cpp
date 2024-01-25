# include <iostream>
# include <fstream>
# include <string>

using namespace std;

// globals
const int DIMENSION1 = 6;
const int DIMENSION2 = 3;
const int DIMENSION3 = 3;


// implement an iterative deepening algorithm, finds solution in 30 steps or less to input rubiks cube


// 0 - white
// 1 - orange
// 2 - green
// 3 - red
// 4 - blue
// 5 - yellow


// take user input 

// starting state is depth 0

void takeInput(int*** initialState) {

    ifstream inputFile("input.txt");

    const int DIMENSION1 = 6;
    const int DIMENSION2 = 3;
    const int DIMENSION3 = 3;

    if (!inputFile.is_open()) {

        cerr << "Failed to open file" << std::endl;
        inputFile.close();
        return;

    } 
    
    else {
        // Append into starting state
        for (int i = 0; i < DIMENSION1; i++) {
            for (int j = 0; j < DIMENSION2; j++) {
                for (int k = 0; k < DIMENSION3; k++) {

                    // Read values from the file and append to initialState
                    if (!(inputFile >> initialState[i][j][k])) {
                        cerr << "Error reading values from the file." << endl;
                        inputFile.close();
                        return;
                    }
                }
            }
        }

        // Close the file
        inputFile.close();
    }
}

// ability to print any cube that is given
void print(int*** array){


    for (int i = 0; i < DIMENSION1; i++){
        for (int j = 0; j < DIMENSION2; j++){
            for (int k = 0; k < DIMENSION3; k++){
              cout << array[i][j][k];
            }
        }
    }

// add the brackets and endl later

}




// now we need to come up as many moves as possible and how the transpose 
// all the moves are with respective to the green center piece

// MOVES


// index map of app pieces to help with writing transpositin functions 

    std::string multilineString = R"(
        
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
     
    )";



int*** left(int*** cube){

// allocate memory for new 3D array

// when a new move is made, there are 20 coordinates in array that are moved (differeeb
int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }

    for (int i = 0; i < DIMENSION1; i++){
        for (int j = 0; j < DIMENSION2; j++){
            for (int k = 0; k < DIMENSION3; k++){
            temp[i][j][k] = cube[i][j][k];
            }
        }
    }

    // now we transpose! 

    // new          original 
    

    // yellow moves to green center piece
    temp[2][0][2] = cube[5][0][2];
    temp[2][1][2] = cube[5][1][2];
    temp[2][2][2] = cube[5][2][2];

    // green moves to white
    temp[0][0][2] = cube[2][0][2];
    temp[0][1][2] = cube[2][1][2];
    temp[0][2][2] = cube[2][2][2];

    // white moves to blue
    temp[4][0][2] = cube[0][0][2];
    temp[4][1][2] = cube[0][1][2];
    temp[4][2][2] = cube[0][2][2];

    // blue moves to yellow
    temp[5][0][2] = cube[4][0][2];
    temp[5][1][2] = cube[4][1][2];
    temp[5][2][2] = cube[4][2][2];

    // these are all transpositions on red face
    temp[3][0][2] = cube[3][0][0];
    temp[3][1][2] = cube[3][0][1];
    temp[3][2][2] = cube[3][0][2];
    temp[3][0][1] = cube[3][1][0];

    temp[3][2][1] = cube[3][1][2];
    temp[3][0][0] = cube[3][2][0];
    temp[3][1][0] = cube[3][2][1];
    temp[3][2][0] = cube[3][2][2];


}


int*** left_prime(int*** cube){
    
int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }

    for (int i = 0; i < DIMENSION1; i++){
        for (int j = 0; j < DIMENSION2; j++){
            for (int k = 0; k < DIMENSION3; k++){
            temp[i][j][k] = cube[i][j][k];
            }
        }
    }

    temp[2][0][2] = cube[5][0][2];
    temp[2][1][2] = cube[5][1][2];
    temp[2][2][2] = cube[5][2][2];

    // green moves to white
    temp[0][0][2] = cube[2][0][2];
    temp[0][1][2] = cube[2][1][2];
    temp[0][2][2] = cube[2][2][2];

    // white moves to blue
    temp[4][0][2] = cube[0][0][2];
    temp[4][1][2] = cube[0][1][2];
    temp[4][2][2] = cube[0][2][2];

    // blue moves to yellow
    temp[5][0][2] = cube[4][0][2];
    temp[5][1][2] = cube[4][1][2];
    temp[5][2][2] = cube[4][2][2];

    // these are all transpositions on red face
    temp[3][0][2] = cube[3][0][0];
    temp[3][1][2] = cube[3][0][1];
    temp[3][2][2] = cube[3][0][2];
    temp[3][0][1] = cube[3][1][0];

    temp[3][2][1] = cube[3][1][2];
    temp[3][0][0] = cube[3][2][0];
    temp[3][1][0] = cube[3][2][1];
    temp[3][2][0] = cube[3][2][2];



    
}



int*** right(){
    

int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
}

int*** right_prime(){

int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
}

int*** up(){

int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
}

int*** up_prime(){
    
int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
}

int*** down(){

int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
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
}

int*** front_prime(){
    
int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
}

int*** back(){
    
int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
}

int*** back_prime(){
    
int*** temp;

temp = new int **[DIMENSION1];

    for (int i = 0; i < DIMENSION1; i++){

        temp[i] = new int *[DIMENSION2];

        for (int j = 0; j < DIMENSION2; j++){
            temp[i][j] = new int[DIMENSION3];
        
        }
    }
}





