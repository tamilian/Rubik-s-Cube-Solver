from random import randint 

# random is for the scramble of the cube

class Piece:

    def __init__(self, position, )

# 3d array representation of cube
def make_cube():
    return [
        [['W','W','W'],['W','W','W'], ['W','W','W']], #Up/White
        [['G','G','G'],['G','G','G'], ['G','G','G']],  #Front/Green
        [['R','R','R'],['R','R','R'], ['R','R','R']],  #Right/Red
        [['O','O','O'],['O','O','O'], ['O','O','O']],   #Left/Orange
        [['Y','Y','Y'],['Y','Y','Y'], ['Y','Y','Y']],   #Down/yellow
        [['B','B','B'],['B','B','B'], ['B','B','B']],   #Back/Blue   
    ]

# dictionary that holds information on rubiks cube pieces
# it will allow us to access each piece within the cube

rubiks_cube = {
    'centers' : {
        'U' : {'colors' : 'white', 'coordinates' : (0,1,1)},  #Up
        'F' : {'colors' : 'white', 'coordinates' : (1,1,1)},  #Front
        'U' : {'colors' : 'white', 'coordinates' : (2,1,1)},  #Right
        'U' : {'colors' : 'white', 'coordinates' : (0,1,1)},  #Left
        'U' : {'colors' : 'white', 'coordinates' : (0,1,1)},  #Down
        'U' : {'colors' : 'white', 'coordinates' : (0,1,1)},  #Back
    },
    'edges' : {
        
        # have a distinction for the pieces in cross to allow for easier solving
        'UF' : {'colors' : ['white', 'green'], 'coordinates' : [(0,2,1),(1,0,0)]},
        'UR' : {'colors' : ['white', 'red'], 'coordinates' : [(0,1,2),(2,0,1)]},
        'UL' : {'colors' : ['white', 'orange'], 'coordinates' : [(0,1,0),(3,0,1)]},
        'UF' : {'colors' : ['white', 'blue'], 'coordinates' : [(0,0,1),(5,0,1)]},
        'FR' : {'colors' : ['white', 'green'], 'coordinates' : [(0,2,1),(1,0,0)]},
        'FL' : {'colors' : ['white', 'green'], 'coordinates' : [(0,2,1),(1,0,0)]},
        'FD' : {'colors' : ['white', 'green'], 'coordinates' : [(0,2,1),(1,0,0)]},





    },

    'corners' : {

    }
}

# initialize cube
cube = make_cube()

def is_cross_solved(cube):  # returns type boolean
    
    white_center_color = cube[0][1][1]  # white center piece 
    




# function to print cube
def print(cube):
    pass

# function to scramble the cube
# randomly scrambe teh cube given a number of moves



