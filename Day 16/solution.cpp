#include <iostream>
#include <map>

using namespace std;

void PrintMap(map<int,char> m) {
  for (int i=0; i<16; i++) {
    cout << m[i] << " ";
  }
  cout << endl;
}

void Spin (map<int,char> & programs, int jump) {
  map<int, char> new_map;
  for (map<int,char>::iterator it = programs.begin(); it != programs.end(); it++) {
    new_map.insert( pair<int,char> ( (it->first + jump) % 16, it->second) );
  }
  programs = new_map;
}

void Exchange (map<int,char> & programs, int pos1, int pos2) {
  char aux = programs[pos1];
  programs[pos1] = programs[pos2];
  programs[pos2] = aux;
}

void Partner (map<int,char> & programs, char prog1, char prog2) {
  int pos1 = -1, pos2 = -1;
  bool found = false;
  map<int,char>::iterator it = programs.begin();
  while (!found && it != programs.end()) {
    if (it->second == prog1) {
      pos1 = it->first;
      if (pos2 != -1)
        found = true;
    } else if (it->second == prog2) {
      pos2 = it->first;
      if (pos1 != -1)
        found = true;
    }
    it++;
  }
  if (pos1 != -1 && pos2 != -1)
    Exchange(programs, pos1, pos2);
  else
    cerr << "Programs " << prog1 << " and " << prog2 << " not found." << endl;
}

string PermutationPromenade() {
  map<int,char> programs;
  char c_in = 'a', prog1, prog2;
  int i_in, pos1, pos2;

  for (int i=0; i<16; i++) {
    programs[i] = c_in;
    c_in++;
  }
  //PrintMap(programs);

  cin >> c_in;
  while (cin) {
    if (c_in == 's') {
      cin >> i_in;
      Spin(programs, i_in);
    } else if (c_in == 'x') {
      cin >> pos1;
      cin >> c_in; // Skip the '/'
      cin >> pos2;
      Exchange(programs, pos1, pos2);
    } else {
      cin >> prog1;
      cin >> c_in; // Skip the '/'
      cin >> prog2;
      Partner(programs, prog1, prog2);
    }

    cin >> c_in; // Skip the ','
    cin >> c_in;
  }

  string result = "";
  for (int i=0; i<16; i++) {
    result += programs[i];
  }
  return result;
}


int main() {
  cout << "\tSolucion: " << PermutationPromenade() << endl;
}
