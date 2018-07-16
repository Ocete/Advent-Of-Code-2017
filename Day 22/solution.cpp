#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

void PrintLayout(vector<vector<char> > &layout) {
  for (int i=0; i<layout.size(); i++) {
    for (int j=0; j<layout.size(); j++) {
      cout << layout[i][j];
    }
    cout << endl;
  }
}

void CreateLayout (vector<vector<char> > &layout) {
  layout.clear();
  string str_read;

  getline(cin, str_read);

  int extra_side = 100, real_side = str_read.size(),
      total_side = 2*extra_side + real_side;

  vector<char> extra_line (total_side, '.');

  for (int i=0; i<extra_side; i++) {
    layout.push_back(extra_line);
  }

  for (int i=0; i<real_side; i++) {
    vector<char> real_line;

    for (int j=0; j<extra_side; j++) {
      real_line.push_back('.');
    }

    for (int j=0; j<real_side; j++) {
      real_line.push_back(str_read[j]);
    }

    for (int j=0; j<extra_side; j++) {
      real_line.push_back('.');
    }

    layout.push_back(real_line);
    getline(cin, str_read);
  }

  for (int i=0; i<extra_side; i++) {
    layout.push_back(extra_line);
  }
}

void AdvancePosition(int &i, int &j, int orientation) {
  switch(orientation) {
    case 0:
      i--;
      break;
    case 1:
      j++;
      break;
    case 2:
      i++;
      break;
    case 3:
      j--;
  }
}

bool Burst (vector<vector<char> > &layout, int &i, int &j, int &orientation) {
  if (i < 0 || j < 0 || i >= layout.size() || j >= layout.size()) {
    cout << "\t OUT OF BOUNDRIES" << endl;
    exit(-1);
  }

  bool infecting = layout[i][j] == '.';

  if (infecting) {
    orientation = (orientation - 1 + 4 ) % 4;
    layout[i][j] = '#';
  } else {
    orientation = (orientation + 1) % 4;
    layout[i][j] = '.';
  }

  AdvancePosition(i, j, orientation);

  return infecting;
}

// 0 = up , 1 = right , 2 = down , 3 = left
int CountInfectingBursts (vector<vector<char> > &layout) {
  int i = layout.size() / 2, j = i, orientation = 0;
  int infecting_bursts = 0;

  for (int k=0; k<10000; k++) {
    infecting_bursts += Burst (layout, i, j, orientation);
  }

  return infecting_bursts;
}

int main() {
  vector<vector<char> > layout;
  CreateLayout(layout);
  //PrintLayout(layout);

  cout << "\tSolucion: " << CountInfectingBursts(layout) << endl;
}
