#include "cube.h"

// overloaded stream insertion operator for Color enum
std::ostream& operator<<(std::ostream& os, const Color& color) {
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

    // default constructor for CubePiece
    CubePiece::CubePiece() : color(WHITE), originalCoordinates(std::make_tuple(0, 0, 0)), currentCoordinates(std::make_tuple(0, 0, 0)) {}

    // parameterized constructor for CubePiece
    CubePiece::CubePiece(Color c, int x, int y, int z) : color(c), originalCoordinates(std::make_tuple(x, y, z)), currentCoordinates(std::make_tuple(x, y, z)) {}

    // assignment operator for CubePiece
    CubePiece& CubePiece::operator=(const CubePiece& other) {
        if (this != &other) { // self-assignment check
            color = other.color;
            originalCoordinates = other.originalCoordinates;
            currentCoordinates = other.currentCoordinates;
        }
        return *this;
    }

    RubiksCube() {
        // Initialize the cube with default colors and coordinates
        int pieceIndex = 0;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    cube[pieceIndex++] = CubePiece(static_cast<Color>(i), i, j, k);
                }
            }
        }
    }

    CubePiece& RubiksCube::operator()(int i, int j, int k) {
        // Operator to access cube pieces by coordinates
        // Check if the indices are within valid range
        if (i < 0 || i >= DIMENSION1 || j < 0 || j >= DIMENSION2 || k < 0 || k >= DIMENSION3) {
            throw std::out_of_range("Index out of range!");
        }
        return cube[i][j][k];
    }



    void RubiksCube::takeInput(const std::string& filename) {
        // Method to initialize the cube with colors from the input file
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

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
                            std::cerr << "Error: Invalid color index in input file." << std::endl;
                            return;
                    }

                    // Set color for the cube piece
                    cube[i][j][k] = CubePiece(color, i, j, k);
                }
            }
        }

        inputFile.close();
    }


    void RubiksCube::originalCoordinateRetrieval(int x, int y, int z){

        // check if input is within bounds
        if (x < 0 || x >= DIMENSION1 || y < 0 || y >= DIMENSION2 || z < 0 || z >= DIMENSION3){
            std::cerr << "Your dimensions are out of bounds" << std::endl;
        }

        // simplify 

        std::tuple<int, int, int> originalCords = cube[x][y][z].originalCoordinates;

        // use get method in tuple to access each original coordinate

        std::cout << "Current Coordinates: (" << x << ", " << y <<  ", " << z <<  ") "
            << "  <- " << " Original Coordinates: "  
            "(" << std::get<0>(originalCords) << ", " << std::get<1>(originalCords) << ", " << std::get<2>(originalCords) << "). " << std::endl;
    }

    // Overloading the != operator
    bool RubiksCube::operator!=(const RubiksCube& other) const {
        for (int i = 0; i < DIMENSION1; i++) {
            for (int j = 0; j < DIMENSION2; j++) {
                for (int k = 0; k < DIMENSION3; k++) {
                    if (cube[i][j][k].color != other.cube[i][j][k].color) {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    void RubiksCube::currentCoordinateRetrieval(int x, int y, int z){

        // check if input is within bounds

        if (x < 0 || x >= DIMENSION1 || y < 0 || y >= DIMENSION2 || z < 0 || z >= DIMENSION3){
            std::cerr << "Your dimensions are out of bounds" << std::endl;
        }

        std::tuple<int, int, int> currentCords = cube[x][y][z].currentCoordinates;

        // use get method in tuple to access each original coordinate

        std::cout << "Original Coordinates of this piece at (" << x << ", " << y <<  ", " << z <<  ") "
            << " are " << std::endl << 
            "(" << std::get<0>(currentCords) << ", " << std::get<1>(currentCords) << ", " << std::get<2>(currentCords) << "). " << std::endl;

    }

    void RubiksCube::printOriginalAndCurrentCoordinates(RubiksCube &c){
        for(int i = 0; i < DIMENSION1; i++){
            std::cout << "--------------------------------" << std::endl;
            for (int j = 0; j < DIMENSION2; j++){
                for(int k = 0; k < DIMENSION3; k++){
                    c.originalCoordinateRetrieval(i,j,k);
                }
            }
            std::cout << "---------------------------------" << std::endl;
        }
    }

    void RubiksCube::printCube() const {
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

    void RubiksCube::rotateFaceVertical(
        Color color1Start, Color color1Dest, int color1KStart, int color1KEnd,

        Color color2Start, Color color2Dest, int color2KStart, int color2KEnd,

        Color color3Start, Color color3Dest, int color3KStart, int color3KEnd,

        Color color4Start, Color color4Dest, int color4KStart, int color4KEnd,

        Color color5, bool clockwise) {


        CubePiece temp[DIMENSION1][DIMENSION2][DIMENSION3]; // Create a temporary CubePiece array

        // Copy cube to temp
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    temp[i][j][k] = cube[i][j][k];
                }
            }
        }

        // SPECIAL CASE
        int a = 2;
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color1Dest)][a][color1KEnd] = cube[static_cast<int>(color1Start)][j][color1KStart];
            temp[static_cast<int>(color1Dest)][a][color1KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color1Dest), a, color1KEnd);
            a--;
        }

        // SPECIAL CASE 
        a = 2;
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color2Dest)][a][color2KEnd] = cube[static_cast<int>(color2Start)][j][color2KStart];
            temp[static_cast<int>(color2Dest)][a][color2KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color2Dest), a,color2KEnd);
            a--;
        }

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color3Dest)][j][color3KEnd] = cube[static_cast<int>(color3Start)][j][color3KStart];
            temp[static_cast<int>(color3Dest)][j][color3KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color3Dest), j, color3KEnd);
        }

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color4Dest)][j][color4KEnd] = cube[static_cast<int>(color4Start)][j][color4KStart];
            temp[static_cast<int>(color4Dest)][j][color4KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color4Dest), j, color4KEnd);

        }

        if (clockwise == true) {
            // perform clockwise rotation
            // update the positions of the elements on the specified face
            temp[static_cast<int>(color5)][0][2] = cube[static_cast<int>(color5)][0][0];
            temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);


            temp[static_cast<int>(color5)][1][2] = cube[static_cast<int>(color5)][0][1];
            temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);


            temp[static_cast<int>(color5)][2][2] = cube[static_cast<int>(color5)][0][2];
            temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 2);



            temp[static_cast<int>(color5)][0][1] = cube[static_cast<int>(color5)][1][0];
            temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);


            temp[static_cast<int>(color5)][2][1] = cube[static_cast<int>(color5)][1][2];
            temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);



            temp[static_cast<int>(color5)][0][0] = cube[static_cast<int>(color5)][2][0];
            temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);


            temp[static_cast<int>(color5)][1][0] = cube[static_cast<int>(color5)][2][1];
            temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);


            temp[static_cast<int>(color5)][2][0] = cube[static_cast<int>(color5)][2][2];
            temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);

        } else if (clockwise == false){
            // perform counterclockwise rotation
            // update the positions of the elements on the specified face
            temp[static_cast<int>(color5)][2][0] = cube[static_cast<int>(color5)][0][0];
            temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);


            temp[static_cast<int>(color5)][1][0] = cube[static_cast<int>(color5)][0][1];
            temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);


            temp[static_cast<int>(color5)][0][0] = cube[static_cast<int>(color5)][0][2];
            temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);

            temp[static_cast<int>(color5)][2][1] = cube[static_cast<int>(color5)][1][0];
            temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);

            temp[static_cast<int>(color5)][0][1] = cube[static_cast<int>(color5)][1][2];
            temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);

            temp[static_cast<int>(color5)][2][2] = cube[static_cast<int>(color5)][2][0];
            temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 2);


            temp[static_cast<int>(color5)][1][2] = cube[static_cast<int>(color5)][2][1];
            temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);


            temp[static_cast<int>(color5)][0][2] = cube[static_cast<int>(color5)][2][2];
            temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);
        
        }
        // Copy rotated cube from temporary cube back to original cube
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    cube[i][j][k] = temp[i][j][k];
                }
            }
        }

    }

    void RubiksCube::rotateFaceHorizontal(

        Color color1Start,  Color color1Dest, 
        
        Color color2Start, Color color2Dest,  
        
        Color color3Start, Color color3Dest, 
        
        Color color4Start, Color color4Dest, 

        Color color5, int jValue,  bool clockwise) {

        CubePiece temp[DIMENSION1][DIMENSION2][DIMENSION3]; // Create a temporary CubePiece array

        // Copy cube to temp
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    temp[i][j][k] = cube[i][j][k];
                }
            }
        }

        for (int k = 0; k < 3; k++) {
            temp[static_cast<int>(color1Dest)][jValue][k] = cube[static_cast<int>(color1Start)][jValue][k];
            temp[static_cast<int>(color1Dest)][jValue][k].currentCoordinates = std::make_tuple(static_cast<int>(color1Dest), jValue, k);
        }

        for (int k = 0; k < 3; k++) {
            temp[static_cast<int>(color2Dest)][jValue][k] = cube[static_cast<int>(color2Start)][jValue][k];
            temp[static_cast<int>(color2Dest)][jValue][k].currentCoordinates = std::make_tuple(static_cast<int>(color2Dest), jValue, k);
        }

        for (int k = 0; k < 3; k++) {
            temp[static_cast<int>(color3Dest)][jValue][k] = cube[static_cast<int>(color3Start)][jValue][k];
            temp[static_cast<int>(color3Dest)][jValue][k].currentCoordinates = std::make_tuple(static_cast<int>(color3Dest), jValue, k);

        }

        for (int k = 0; k < 3; k++) {
            temp[static_cast<int>(color4Dest)][jValue][k] = cube[static_cast<int>(color4Start)][jValue][k];
            temp[static_cast<int>(color4Dest)][jValue][k].currentCoordinates = std::make_tuple(static_cast<int>(color4Dest), jValue, k);
        }

        if (clockwise) {
            // perform clockwise rotation
            // update the positions of the elements on the specified face
            temp[static_cast<int>(color5)][0][2] = cube[static_cast<int>(color5)][0][0];
            temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);


            temp[static_cast<int>(color5)][1][2] = cube[static_cast<int>(color5)][0][1];
            temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);


            temp[static_cast<int>(color5)][2][2] = cube[static_cast<int>(color5)][0][2];
            temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 2);


            temp[static_cast<int>(color5)][0][1] = cube[static_cast<int>(color5)][1][0];
            temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);


            temp[static_cast<int>(color5)][2][1] = cube[static_cast<int>(color5)][1][2];
            temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);


            temp[static_cast<int>(color5)][0][0] = cube[static_cast<int>(color5)][2][0];
            temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);


            temp[static_cast<int>(color5)][1][0] = cube[static_cast<int>(color5)][2][1];
            temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);


            temp[static_cast<int>(color5)][2][0] = cube[static_cast<int>(color5)][2][2];
            temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);

        } else {
            // perform counterclockwise rotation
            // update the positions of the elements on the specified face
            temp[static_cast<int>(color5)][2][0] = cube[static_cast<int>(color5)][0][0];
            temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);

            temp[static_cast<int>(color5)][1][0] = cube[static_cast<int>(color5)][0][1];
            temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);

            temp[static_cast<int>(color5)][0][0] = cube[static_cast<int>(color5)][0][2];
            temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);

            temp[static_cast<int>(color5)][2][1] = cube[static_cast<int>(color5)][1][0];
            temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);

            temp[static_cast<int>(color5)][0][1] = cube[static_cast<int>(color5)][1][2];
            temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);

            temp[static_cast<int>(color5)][2][2] = cube[static_cast<int>(color5)][2][0];
            temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 2);

            temp[static_cast<int>(color5)][1][2] = cube[static_cast<int>(color5)][2][1];
            temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);

            temp[static_cast<int>(color5)][0][2] = cube[static_cast<int>(color5)][2][2];
            temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);


        }

        // copy rotated cube from temporary cube back to original cube
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    cube[i][j][k] = temp[i][j][k];
                }
            }
        }
    }

    void RubiksCube::rotateFront( 
    Color color1Start, Color color1Dest, int color1JStart, int color1KEnd,  

    Color color2Start,Color color2Dest, int color2KStart , int color2JEnd,  

    Color color3Start,Color color3Dest, int color3JStart, int color3JEnd, 

    Color color4Start,Color color4Dest, int color4KStart, int color4JEnd,

    Color color5){
 
    CubePiece temp[DIMENSION1][DIMENSION2][DIMENSION3]; // Create a temporary CubePiece array

        // Copy cube to temp
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    temp[i][j][k] = cube[i][j][k];
                }
            }
        }

    // move 1 (white face start)
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color1Dest)][j][color1KEnd] = cube[static_cast<int>(color1Start)][color1JStart][j];
            temp[static_cast<int>(color1Dest)][j][color1KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color1Dest), j, color1KEnd);

        }

    // move 2
        int a = 2;
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color2Dest)][color2JEnd][a] = cube[static_cast<int>(color2Start)][j][color2KStart];
            temp[static_cast<int>(color2Dest)][color2JEnd][a].currentCoordinates = std::make_tuple(static_cast<int>(color2Dest), color2JEnd,a);
            a--;
        }

    // move 3

        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color3Dest)][j][color3JEnd] = cube[static_cast<int>(color3Start)][color3JStart][j];
            temp[static_cast<int>(color3Dest)][j][color3JEnd].currentCoordinates = std::make_tuple(static_cast<int>(color3Dest), j,color3JEnd );
        }
    // move 4
        a = 2;
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color4Dest)][color4JEnd][a] = cube[static_cast<int>(color4Start)][j][color4KStart];
            temp[static_cast<int>(color4Dest)][color4JEnd][a].currentCoordinates = std::make_tuple(static_cast<int>(color4Dest), color4JEnd,a);
            a--;
        }  

        // perform clockwise rotation

        temp[color5][0][2] = cube[color5][0][0];
        temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);

        temp[color5][1][2] = cube[color5][0][1];
        temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);

        temp[color5][2][2] = cube[color5][0][2];
        temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 2);

        temp[color5][0][1] = cube[color5][1][0];
        temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);

        temp[color5][2][1] = cube[color5][1][2];
        temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);

        temp[color5][0][0] = cube[color5][2][0];
        temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);

        temp[color5][1][0] = cube[color5][2][1];
        temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);

        temp[color5][2][0] = cube[color5][2][2];
        temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);


    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
}

    void RubiksCube::rotateBack( 
    Color color1Start, Color color1Dest, int color1JStart, int color1KEnd,  

    Color color2Start,Color color2Dest, int color2KStart , int color2JEnd,  

    Color color3Start,Color color3Dest, int color3JStart, int color3KEnd, 

    Color color4Start,Color color4Dest, int color4KStart, int color4JEnd,

    Color color5){
 
    CubePiece temp[DIMENSION1][DIMENSION2][DIMENSION3]; // Create a temporary CubePiece array

        // Copy cube to temp
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    temp[i][j][k] = cube[i][j][k];
                }
            }
        }

    // move 1 (white face start) , fucks sake, the a is not working, why??

        int a = 2;
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color1Dest)][a][color1KEnd] = cube[static_cast<int>(color1Start)][color1JStart][j];
            temp[static_cast<int>(color1Dest)][a][color1KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color1Dest), a, color1KEnd);
            a--;
        }

    // move 2
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color2Dest)][color2JEnd][j] = cube[static_cast<int>(color2Start)][j][color2KStart];
            temp[static_cast<int>(color2Dest)][color2JEnd][j].currentCoordinates = std::make_tuple(static_cast<int>(color2Dest), color2JEnd, j);
        }

    // move 3
        
        a = 2;
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color3Dest)][a][color3KEnd] = cube[static_cast<int>(color3Start)][color3JStart][j];
            temp[static_cast<int>(color3Dest)][a][color3KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color3Dest), a, color3KEnd);
            a--;
        }
    // move 4
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color4Dest)][color4JEnd][j] = cube[static_cast<int>(color4Start)][j][color4KStart];
            temp[static_cast<int>(color4Dest)][color4JEnd][j].currentCoordinates = std::make_tuple(static_cast<int>(color4Dest), color4JEnd, j);
        }  

        // perform clockwise rotation

        temp[color5][0][2] = cube[color5][0][0];
        temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);

        temp[color5][1][2] = cube[color5][0][1];
        temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);

        temp[color5][2][2] = cube[color5][0][2];
        temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 2);

        temp[color5][0][1] = cube[color5][1][0];
        temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);

        temp[color5][2][1] = cube[color5][1][2];
        temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);

        temp[color5][0][0] = cube[color5][2][0];
        temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);

        temp[color5][1][0] = cube[color5][2][1];
        temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);

        temp[color5][2][0] = cube[color5][2][2];
        temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);


    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
}

    void RubiksCube::rotateFrontCounterClockwise( 

    Color color1Start, Color color1Dest, int color1JStart , int color1KEnd,  

    Color color2Start,Color color2Dest, int color2KStart, int color2JEnd ,

    Color color3Start,Color color3Dest, int color3JStart , int color3KEnd,

    Color color4Start,Color color4Dest, int color4KStart, int color4JEnd, 

    Color color5){
 
    CubePiece temp[DIMENSION1][DIMENSION2][DIMENSION3]; // create a temporary CubePiece array

        // Copy cube to temp
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    temp[i][j][k] = cube[i][j][k];
                }
            }
        }

    // move 1: always start from white
    // back prime: white to red
    // front prime:
        int a = 2; 
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color1Dest)][a][color1KEnd] = cube[static_cast<int>(color1Start)][color1JStart][j];
            temp[static_cast<int>(color1Dest)][a][color1KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color1Dest), a, color1KEnd);
        }
    // move 2 (a variable)
    // back prime: red to yellow
    // front prime:  
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color2Dest)][color2JEnd][j] = cube[static_cast<int>(color2Start)][j][color2KStart];
            temp[static_cast<int>(color2Dest)][color2JEnd][j].currentCoordinates = std::make_tuple(static_cast<int>(color2Dest), color2JEnd, j);
        }

    // move 3
    // back prime: yellow to orange
    // front prime: 
        a = 2;
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color3Dest)][a][color3KEnd] = cube[static_cast<int>(color3Start)][color3JStart][j];
            temp[static_cast<int>(color3Dest)][a][color3KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color3Dest),a ,color3KEnd);
            a--;
        }
    // move 4 (a variable)
    // back prime: orange to white
    // front prime: 
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color4Dest)][color4JEnd][j] = cube[static_cast<int>(color4Start)][j][color4KStart];
            temp[static_cast<int>(color4Dest)][color4JEnd][j].currentCoordinates = std::make_tuple(static_cast<int>(color4Dest), color4JEnd, j);
        }  

        // perform counterclockwise rotation
        // update the positions of the elements on the specified face

        temp[color5][2][0] = cube[color5][0][0];
        temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);

        temp[color5][1][0] = cube[color5][0][1];
        temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);

        temp[color5][0][0] = cube[color5][0][2];
        temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);


        temp[color5][2][1] = cube[color5][1][0];
        temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);

        temp[color5][0][1] = cube[color5][1][2];
        temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);

        temp[color5][2][2] = cube[color5][2][0];
        temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2 ,2);

        temp[color5][1][2] = cube[color5][2][1];
        temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);

        temp[color5][0][2] = cube[color5][2][2];
        temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);

    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
}

    void RubiksCube::rotateBackCounterClockWise( 

    Color color1Start, Color color1Dest, int color1JStart, int color1KEnd,  

    Color color2Start,Color color2Dest, int color2KStart, int color2JEnd ,

    Color color3Start,Color color3Dest, int color3JStart , int color3KEnd ,

    Color color4Start,Color color4Dest, int color4KStart , int color4JEnd, 

    Color color5){
 
    CubePiece temp[DIMENSION1][DIMENSION2][DIMENSION3]; // Create a temporary CubePiece array

        // Copy cube to temp
        for (int i = 0; i < DIMENSION1; ++i) {
            for (int j = 0; j < DIMENSION2; ++j) {
                for (int k = 0; k < DIMENSION3; ++k) {
                    temp[i][j][k] = cube[i][j][k];
                }
            }
        }

    // move 1: always start from white
    // back prime: white to red
    // front prime: 
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color1Dest)][j][color1KEnd] = cube[static_cast<int>(color1Start)][color1JStart][j];
            temp[static_cast<int>(color1Dest)][j][color1KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color1Dest), j, color1KEnd);
        }
    // move 2 (a variable)
    // back prime: red to yellow
    // front prime:
        int a = 2;  
        for (int j = 0; j < 3; j++) {
            // logic error is here 3,0,2 should be transferred to 5,2,2
            temp[static_cast<int>(color2Dest)][color2JEnd][a] = cube[static_cast<int>(color2Start)][j][color2KStart];
            temp[static_cast<int>(color2Dest)][color2JEnd][a].currentCoordinates = std::make_tuple(static_cast<int>(color2Dest), color2JEnd, a);
            a--; // this should decrement to 0
        }

    // move 3
    // back prime: yellow to orange
    // front prime: 
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color3Dest)][j][color3KEnd] = cube[static_cast<int>(color3Start)][color3JStart][j];
            temp[static_cast<int>(color3Dest)][j][color3KEnd].currentCoordinates = std::make_tuple(static_cast<int>(color3Dest), j, color3KEnd);
        }
    // move 4 (a variable)
    // back prime: orange to white
    // front prime:
        a = 2; 
        for (int j = 0; j < 3; j++) {
            temp[static_cast<int>(color4Dest)][color4JEnd][a] = cube[static_cast<int>(color4Start)][j][color4KStart];
            temp[static_cast<int>(color4Dest)][color4JEnd][a].currentCoordinates = std::make_tuple(static_cast<int>(color4Dest), color4JEnd, a);
            a--;
        }  

        // perform counterclockwise rotation
        // update the positions of the elements on the specified face

        temp[color5][2][0] = cube[color5][0][0];
        temp[static_cast<int>(color5)][2][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 0);

        temp[color5][1][0] = cube[color5][0][1];
        temp[static_cast<int>(color5)][1][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 0);

        temp[color5][0][0] = cube[color5][0][2];
        temp[static_cast<int>(color5)][0][0].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 0);


        temp[color5][2][1] = cube[color5][1][0];
        temp[static_cast<int>(color5)][2][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2, 1);

        temp[color5][0][1] = cube[color5][1][2];
        temp[static_cast<int>(color5)][0][1].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 1);

        temp[color5][2][2] = cube[color5][2][0];
        temp[static_cast<int>(color5)][2][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 2 ,2);

        temp[color5][1][2] = cube[color5][2][1];
        temp[static_cast<int>(color5)][1][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 1, 2);

        temp[color5][0][2] = cube[color5][2][2];
        temp[static_cast<int>(color5)][0][2].currentCoordinates = std::make_tuple(static_cast<int>(color5), 0, 2);

    // copy rotated cube from  temporary cube back to original cube
    for (int i = 0; i < DIMENSION1; ++i) {
        for (int j = 0; j < DIMENSION2; ++j) {
            for (int k = 0; k < DIMENSION3; ++k) {
                cube[i][j][k] = temp[i][j][k];
            }
        }
    }
}
        // Right move function ( in respect to green face)
        void RubiksCube::right() { // vertical funciton
            rotateFaceVertical(WHITE, BLUE, 2, 0, BLUE, YELLOW, 0, 2, YELLOW, GREEN, 2, 2, GREEN, WHITE, 2, 2, RED, true);
        }

        void RubiksCube::right_prime(){    // vertical function
            rotateFaceVertical(YELLOW, BLUE, 2,0, BLUE, WHITE, 0,2, WHITE, GREEN, 2, 2, GREEN, YELLOW, 2, 2, RED, false);
        }

        void RubiksCube::left(){        // vertical function
            rotateFaceVertical(YELLOW, BLUE, 0,2, BLUE, WHITE, 2, 0, WHITE, GREEN, 0,0, GREEN, YELLOW, 0,0, ORANGE, true);
        }

        void RubiksCube::left_prime(){  // vertical function
            rotateFaceVertical(WHITE, BLUE, 0, 2, BLUE, YELLOW, 2,0, YELLOW, GREEN, 0,0, GREEN, WHITE, 0,0, ORANGE, false);
        }

        void RubiksCube::up(){ // horizontal function
            rotateFaceHorizontal(GREEN, ORANGE, ORANGE, BLUE, BLUE, RED, RED, GREEN, WHITE, 0, true);
        }

        void RubiksCube::up_prime(){ // horizontal function
            rotateFaceHorizontal(GREEN,RED, RED, BLUE, BLUE, ORANGE, ORANGE, GREEN, WHITE, 0,  false);
        }

        void RubiksCube::down(){ // horizontal function
            rotateFaceHorizontal(GREEN, RED, RED, BLUE, BLUE, ORANGE, ORANGE, GREEN, YELLOW, 2, true);
        }

        void RubiksCube::down_prime(){ // horizontal function
            rotateFaceHorizontal(GREEN , ORANGE, ORANGE, BLUE, BLUE, RED, RED, GREEN, YELLOW, 2, false);
        }


        void RubiksCube::front(){ // clockwise
            rotateFront(WHITE, RED, 2, 0, RED, YELLOW, 0, 0, YELLOW, ORANGE, 2, 0, ORANGE, WHITE,2, 2, GREEN);
        }

        void RubiksCube::back(){ // clockwise
            rotateBack(WHITE, ORANGE, 0, 0, ORANGE, YELLOW, 0, 2, YELLOW, RED, 2, 2, RED, WHITE, 2, 0, BLUE);
        }

        void RubiksCube::front_prime(){ // counterclockwise
            rotateFrontCounterClockwise(WHITE, ORANGE, 2, 2, ORANGE, YELLOW, 2, 0, YELLOW, RED, 0, 0, RED, WHITE, 0, 2, GREEN); 
        }

        void RubiksCube::back_prime(){ // counterclockwise
            rotateBackCounterClockWise(WHITE, RED, 0, 2, RED, YELLOW, 2, 2, YELLOW, ORANGE, 2, 0, ORANGE, WHITE, 0, 0, BLUE);
        }

void RubiksCube::scramble(int numMoves) {
    // open a file for writing
    std::ofstream outputFile("scramble_moves.txt");

    RubiksCube solvedState;
    solvedState.takeInput("solution.txt");

    if(outputFile.is_open()) {
        for (int i = 0; i < numMoves; i++) {
            // use rand, then use modulus and it will give us random numbers from 0 to 11
            int move = rand() % 12;

            switch(move) {
                case 0:
                    solvedState.right(); break;
                case 1:
                    solvedState.right_prime(); break;
                case 2:
                    solvedState.left(); break;
                case 3:
                    solvedState.left_prime(); break;
                case 4:
                    solvedState.up(); break;
                case 5:
                    solvedState.up_prime(); break;
                case 6:
                    solvedState.down(); break;
                case 7:
                    solvedState.down_prime(); break;
                case 8:
                    solvedState.front(); break;
                case 9:
                    solvedState.front_prime(); break;
                case 10:
                    solvedState.back(); break;
                case 11:
                    solvedState.back_prime(); break;
            }
        }

        for(int i = 0; i < DIMENSION1; i++) {
            for(int j = 0; j < DIMENSION2; j++) {
                for(int k = 0; k < DIMENSION3; k++) {
                    outputFile << static_cast<int>(solvedState(i,j,k).color) << " ";
                }
            }
        }

        outputFile.close(); // close the output file
    }
}

/*
int main() {
    RubiksCube cube;


    cube.scramble(1);


}*/




    
