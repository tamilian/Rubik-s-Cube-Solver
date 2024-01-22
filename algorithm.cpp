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

void takeInput(int ***initialState) {

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
void print(int *** array){


    for (int i = 0; i < DIMENSION1; i++){
        for (int j = 0; j < DIMENSION2){
            for (int k = 0; k < DIMENSION3){
              cout << array[i][j][k];
            }
        }
    }

// add the brackets and endl later

}




// now we need to come up as many moves as possible and how the transpose 
// all the moves are with respective to the green phase
// it was discussed that that was all we really needed, it ticks the boxes for all the moves that are needed


// MOVES

int*** left(int*** cube){


// allocate memory for new 3D array
int *** temp;

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
            temp[i][j][k] = cube[i][j][k]
            }
        }
    }

    // now we transpose 
    



}





int*** left_prime();

int*** right();

int*** right_prime();

int*** up();

int*** up_prime();

int*** down();

int*** down_prime();

int*** front();

int*** front_prime();

int*** back();

int*** back_prime();

