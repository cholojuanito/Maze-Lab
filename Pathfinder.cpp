#include "Pathfinder.h"

string Pathfinder::toString() const
{
    stringstream ss;
    int maze[5][5][5];
    for (int i = 0; i<4; i++){
      for (int j = 0; j<4; i++){
        for (int k = 0; k<4; i++){
      ss << maze[i][j][k];
    }
    ss << endl;
  }
  ss << endl;
}
  return ss.str();  
}

/*
* createRandomMaze
*
* Generates a random maze and stores it as the current maze.
*
* The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
* in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
* solvable or unsolvable, and this method should be able to produce both kinds of mazes.
*/
void Pathfinder::createRandomMaze()
{
int maze[5][5][5];
for (int i = 0; i<4; i++){
  for (int j = 0; j<4; i++){
    for (int k = 0; k<4; i++){
      maze[i][j][k]= rand()%2;
    }
  }
}
  maze[0][0][0]=1;
  maze[4][4][4]=1;   
}
//-----------------------------------------------------------------------------------------

//Part 2-----------------------------------------------------------------------------------
/*
* importMaze
*
* Reads in a maze from a file with the given file name and stores it as the current maze.
* Does nothing if the file does not exist or if the file's data does not represent a valid
* maze.
*
* The file's contents must be of the format described above to be considered valid.
*
* Parameter:	file_name
*				The name of the file containing a maze
* Returns:		bool
*				True if the maze is imported correctly; false otherwise
*/
bool Pathfinder::importMaze(string file_name)
{
int maze[5][5][5];

  cout << "importMaze from "<<file_name<<endl;
  ifstream file (file_name.c_str());
  if (file.is_open()) {
    string line;
      for (int i = 0; i<4; i++){
      getline(file, line);
      stringstream ss(line);
      for (int j = 0; j<4; j++){
        int value;
        ss >> value;
        for (int k = 0; k<4; k++) {
          maze[i][j][k] = value;
        }
        // cout << "["<<row<<"]["<<col<<"]="<<value<<endl;
      }
    }
  }
    return(true);
}
//-----------------------------------------------------------------------------------------


bool Pathfinder::find_maze_path(int maze[5][5][5], int x, int y, int z) 
{
  cout << "find_maze_path ["<<x<<"]["<<y<<"]["<<z<<"]"<<endl;
  cout << this->toString();
  if (x < 0 || y < 0 || z < 0 || x >= 5 || y >= 5 || z >= 5)
    return false;      // Cell is out of bounds.
  else if (maze[x][y][z] != BACKGROUND)
    return false;      // Cell is on barrier or dead end.
  else if (x == 4 && y == 4 && z==5) {
    maze[x][y][z] = PATH;         // Cell is on path
    solution.push_back("("+to_string(r)+","+to_string(c)+")");
    return true;               // and is maze exit.
  }
  else { 
    // Recursive case.
    // Attempt to find a path from each neighbor.
    // Tentatively mark cell as on path.
    maze[x][y][z] = PATH;
    if (find_maze_path(maze, r - 1, c)
        || find_maze_path(maze, r + 1, c)
        || find_maze_path(maze, r, c - 1)
        || find_maze_path(maze, r, c + 1 ) ) {
      solution.push_back("("+to_string(r)+","+to_string(c)+")");
      return true;
    }
    else {
      grid[r][c] = TEMPORARY;  // Dead end.
      return false;
    }
  }
}
  //Part 3-----------------------------------------------------------------------------------
/*
* solveMaze
*
* Attempts to solve the current maze and returns a solution if one is found.
*
* A solution to a maze is a list of coordinates for the path from the entrance to the exit
* (or an empty vector if no solution is found). This list cannot contain duplicates, and
* any two consecutive coordinates in the list can only differ by 1 for only one
* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
* where x, y, and z are the integer coordinates of a cell.
*
* Understand that most mazes will contain multiple solutions
*
* Returns:		vector<string>
*				A solution to the current maze, or an empty vector if none exists
*/

vector<string> Pathfinder::solveMaze()
{
  find_maze_path(maze_grid, 0,0);
  for(auto s:solution) {
    cout <<s<<endl;
  }
    return solution;
}
