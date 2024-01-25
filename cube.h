#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <fstream>
#include <string>

class RubiksCube {
private:
    int*** cube;

    const int DIMENSION1 = 6;
    const int DIMENSION2 = 3;
    const int DIMENSION3 = 3;

public:
    RubiksCube();
    ~RubiksCube();
    void takeInput();
    void print();
    void left();
    void left_prime();
    void right();
    void right_prime();
    void up();
    void up_prime();
    void down();
    void down_prime();
    void front();
    void front_prime();
    void back();
    void back_prime();
};

#endif // RUBIKSCUBE_H
