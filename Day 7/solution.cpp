#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

void ReadLine(vector<string> & v) {
  v.clear();
  string str;
  getline(cin, str);
  istringstream iss(str);
  copy(istream_iterator<string>(iss),
       istream_iterator<string>(),
       back_inserter(v));
}

string Root() {
  vector<string> v;
  set<string> parents, children;
  string aux;
  while(cin) {
    ReadLine(v);
    parents.insert(v[0]);
    for (int i=3; i<v.size(); i++) {
      aux = v[i];
      if (aux[aux.length()-1] == ',') {
        aux = aux.substr(0, aux.length()-1);
      }
      children.insert(aux);
    }
  }
  for (set<string>::iterator it = parents.begin(); it != parents.end(); it++) {
    if (children.count(*it) == 0) {
      return *it;
    }
  }
  return "ERROR";
}

int main() {
  vector<string> v;
  cout << "\tSolucion: " << Root() << endl;
}
