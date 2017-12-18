#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

void PrintMap(map<int,char> m) {
  for (int i=0; i<16; i++) {
    cout << m[i] << " ";
  }
  cout << endl;
}

void Spin (map<int,char> & dancers, int jump) {
  map<int, char> new_map;
  int mod = dancers.size();
  for (map<int,char>::iterator it = dancers.begin(); it != dancers.end(); it++) {
    new_map.insert( pair<int,char> ( (it->first + jump) % mod, it->second) );
  }
  dancers = new_map;
}

void Exchange (map<int,char> & dancers, int pos1, int pos2) {
  char aux = dancers[pos1];
  dancers[pos1] = dancers[pos2];
  dancers[pos2] = aux;
}

void Partner (map<int,char> & dancers, char prog1, char prog2) {
  int pos1 = -1, pos2 = -1;
  bool found = false;
  map<int,char>::iterator it = dancers.begin();
  while (!found && it != dancers.end()) {
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
    Exchange(dancers, pos1, pos2);
  else
    cerr << "Programs " << prog1 << " and " << prog2 << " not found." << endl;
}

void Dance(map<int,char> & dancers) {
  fstream file;
  int pos1, pos2, i_in;
  char prog1, prog2;
  char c_in;

  file.open("input.txt", fstream::in);
  file >> c_in;
  while (file) {
    if (c_in == 's') {
      file >> i_in;
      Spin(dancers, i_in);
    } else if (c_in == 'x') {
      file >> pos1;
      file >> c_in; // Skip the '/'
      file >> pos2;
      Exchange(dancers, pos1, pos2);
    } else {
      file >> prog1;
      file >> c_in; // Skip the '/'
      file >> prog2;
      Partner(dancers, prog1, prog2);
    }

    file >> c_in; // Skip the ','
    file >> c_in;
  }

  file.close();
}

string MapToString(map<int,char> & dancers) {
  string result = "";
  for (int i=0; i<dancers.size(); i++) {
    result += dancers[i];
  }
  return result;
}

string PermutationPromenade() {
  map<int,char> dancers;
  char c = 'a';
  string result;
  map<string, int> configurations;

  for (int i=0; i<16; i++) {
    dancers[i] = c;
    c++;
  }
  //PrintMap(dancers);
  result = MapToString(dancers);

  do {
    configurations.insert(pair<string,int> (result, configurations.size()) );

    Dance(dancers);
    result = MapToString(dancers);

  } while (configurations.count(result) == 0);

  // Using that the dancers repeat the same configuration afeter some iterations
  int mod = configurations.size() + 1,
      total_it = 1000000000 % mod + configurations[result]-1;

  c = 'a';
  for (int i=0; i<16; i++) {
    dancers[i] = c;
    c++;
  }

  for (int i=0; i<total_it; i++)
    Dance(dancers);

  return MapToString(dancers);
}


int main() {
  cout << "\tSolucion: " << PermutationPromenade() << endl;
}
