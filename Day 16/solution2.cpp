#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>
using namespace std;

int LetterToIndex (char c) {
  return c - 'a';
}

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

void StringToMap (map<int, char> &m, const string &str) {
  m.clear();
  for (int i=0; i<str.size(); i++) {
    m[i] = str[i];
  }
}

string Dance(string &dancers) {
  //cout << "Before core" << endl;

  fstream file;
  map<int,char> programs;
  char prog1, prog2, c_in;
  int i_in, pos1, pos2;

  StringToMap(programs, dancers);
  //PrintMap(programs);

  file.open("input.txt", fstream::in);
  file >> c_in;
  while (file) {
    if (c_in == 's') {
      file >> i_in;
      Spin(programs, i_in);
    } else if (c_in == 'x') {
      file >> pos1;
      file >> c_in; // Skip the '/'
      file >> pos2;
      Exchange(programs, pos1, pos2);
    } else {
      file >> prog1;
      file >> c_in; // Skip the '/'
      file >> prog2;
      Partner(programs, prog1, prog2);
    }

    file >> c_in; // Skip the ','
    file >> c_in;
  }

  for (int i=0; i<16; i++) {
    dancers[i] = programs[i];
  }


  file.close();
  //cout << "After core" << endl;
}

string PermutationPromenade() {
  string dancers = "abcdefghijklmnop";
  string result;
  map<string, int> configurations;
  int i=0;

  do {
    cout << i << " -> " << dancers << endl;
    configurations[dancers] = i;

    Dance(dancers);
    i++;
  } while (configurations.count(dancers) == 0);

  //cout << "HIT: " << dancers << endl;

  // Using that the dancers repeat the same configuration after some iterations
  int it_before_loop = configurations[dancers];
  int resting_iterations = 1000000000 - it_before_loop;
  int mod = i - it_before_loop;
  resting_iterations =  resting_iterations % mod;

  for (int j=0; j<resting_iterations; j++)
    Dance(dancers);

  //cout << it_before_loop << " " << mod << " " << i << " " << resting_iterations << endl;

  return dancers;
}


int main() {
  cout << "\tSolucion: " << PermutationPromenade() << endl;
}
