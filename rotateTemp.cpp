    // all my calculations for how the transpositions work under the hood
    // will be used to test the function throughly before implmenting ID algorithm (BFS)
    
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