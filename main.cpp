/*
    Name: Mary Bolton
    Date: 4/12/2017
    Class: CS142
    Pledge: I have neither given nor received unauthorized aid on this program.
    Description: This program simulates the Triwizard Tournament Maze and Harry's journey
    to find the cup.
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/*
    This function reads the maze in from a file.
    Parameters: filename, the name of the file we want to read.
    Returns: a vector of strings representing each line of the file.
*/
vector<string> read_file (string filename){

    string row;
    vector<string> maze;

    ifstream infile (filename);

    if (!infile.is_open()) {
        cout << "Could not open game file." << endl;
    }


    while(!infile.eof()){
        infile >> row;
        maze.push_back(row);
    }

    infile.close();
    return maze;

}


/*
    This function prints the current state of the maze.
    Parameters: maze, the vector of strings that represents each line of the file.
    Returns: none.
*/
void print_current_state(vector <string> maze){

    for (int i = 0; i <= maze.size() - 1; i++){
        cout << maze[i] << endl;
    }

}


/*
    This function locates Harry within the maze.
    Parameters: maze, the vector of strings that represents each line of the file. row, the x coordinate of
    Harry's location, passed by reference. col, the y coordinate of Harry's location, passed by reference.
    Returns: none.
*/
void find_harry (vector <string> maze, int & row, int & col) {

    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'H') {
                col = j;
                row = i;
            }
        }
    }
}



/*
    This function solves the maze recursively.
    Parameters: maze, the vector of strings that represents each line of the file. row, the x coordinate of
    Harry's location. col, the y coordinate of Harry's location. numcalls, the number of times the solve function
    has been called, passed by reference.
    Returns: the string of directions from Harry's starting point to the cup.
*/
string solve(vector<string> maze, int row, int col, int & numcalls){

    numcalls += 1;
    string path;

    cout << "Harry is at (" << row << "," << col << "). ";

    if (maze[row][col] == 'C'){
        cout << "Congratulations! Harry has found the cup!" << endl; //base case
        return "C";
    }
    else{
        cout << "He has not found the cup yet!" << endl;

        maze[row][col] = 'o';

        print_current_state(maze);

        if (row-1 >= 0 && maze[row-1][col] != '#' && maze[row-1][col] != 'o'){
            path = solve (maze, row-1, col, numcalls); //moves Harry north
            if (path != "X"){
                return "N" + path;
            }
        }
        if (row+1 <= maze.size() && maze[row+1][col] != '#' && maze[row+1][col] != 'o'){
            path = solve (maze, row+1, col, numcalls); //moves Harry south
            if (path != "X"){
                return "S" + path;
            }
        }
        if (col+1 <= maze[row].size() && maze[row][col+1] != '#' && maze[row][col+1] != 'o'){
            path = solve (maze, row, col+1, numcalls); //moves Harry east
            if (path != "X"){
                return "E" + path;
            }
        }
        if (col-1 >= 0 && maze[row][col-1] != '#' && maze[row][col-1] != 'o'){
            path = solve (maze, row, col-1, numcalls); //moves Harry west
            if (path != "X"){
                return "W" + path;
            }
        }
        maze[row][col] = '.';
        return "X";
    }
}


int main(){

    string filename, game_over;
    int row, col, numcalls;
    vector <string> maze;


    cout << "Enter filename: " << endl;
    cin >> filename;


    maze = read_file(filename);

    print_current_state(maze);
    find_harry(maze, row, col);

    string path = solve(maze, row, col, numcalls);
    cout << "Solution: " << path << endl;
    cout << "Solve was called " << numcalls << "times." << endl;



}


