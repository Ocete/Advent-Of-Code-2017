#include <iostream>
#include <vector>

using namespace std;

void ReadMaze (vector<vector<char> > & maze) {
  maze.clear();
  string str;

  getline(cin, str, '\n');
  while (cin) {
    vector<char> newline;
    for (int i=0; i<str.length(); i++) {
      if (str[i] == '\t') {
        newline.push_back(' ');
        newline.push_back(' ');
      } else {
        newline.push_back(str[i]);
      }
    }
    maze.push_back(newline);
    getline(cin, str, '\n');
  }
}

void BeginMaze(vector<vector<char> > & maze, int & pos_i, int & pos_j) {
  pos_i = pos_j = 0;
  bool found = false;
  while (!found) {
    if (maze[0][pos_j] == '|') {
      found = true;
    } else {
      pos_j++;
    }
  }
}

void TakeAStep(int & pos_i, int & pos_j, char direction) {
  if (direction == 'n')
    pos_i--;
  else if (direction == 's')
    pos_i++;
  else if (direction == 'e')
    pos_j++;
  else if (direction == 'w')
    pos_j--;
  else
    cout << "This should never appear - TakeAStep " << endl;
}

void ChangeDirection(vector<vector<char> > & maze, int & pos_i, int & pos_j,
      char & direction) {
  if ( pos_i>0 && direction!='s' && maze[pos_i-1][pos_j]!=' ' ) {
    pos_i--;
    direction = 'n';
  } else if ( pos_i<maze.size()-1 && direction!='n' && maze[pos_i+1][pos_j]!=' ' ) {
    pos_i++;
    direction = 's';
  } else if ( pos_j>0 && direction!='e' && maze[pos_i][pos_j-1]!=' ' ) {
    pos_j--;
    direction = 'w';
  } else if ( pos_j<maze[pos_i].size()-1 && direction!='w' && maze[pos_i][pos_j+1]!=' ' ) {
    pos_j++;
    direction = 'e';
  } else {
    cout << "This should never appear - ChangeDirection " << endl;
  }
}

void Move(vector<vector<char> > & maze, int & pos_i, int & pos_j,
      char & direction, string & result) {
  if (maze[pos_i][pos_j] == '|' || maze[pos_i][pos_j] == '-') {
    TakeAStep(pos_i, pos_j, direction);
  } else if (maze[pos_i][pos_j] == '+') {
    ChangeDirection(maze, pos_i, pos_j, direction);
  } else if (maze[pos_i][pos_j] >= 'A' && maze[pos_i][pos_j] <= 'Z') {
    result += maze[pos_i][pos_j];
    TakeAStep(pos_i, pos_j, direction);
  } else {
    cout << "This should never appear - Move " << endl;
  }
}

string SeriesOfTubes() {
  vector<vector<char> > maze;
  string result;
  int pos_i, pos_j;
  char direction = 's';

  ReadMaze(maze);
  BeginMaze(maze, pos_i, pos_j);

  while (maze[pos_i][pos_j] != ' ') {
    Move(maze, pos_i, pos_j, direction, result);
  }

  return result;
}


int main() {
  cout << "\tSolucion: " << SeriesOfTubes() << endl;
}
