#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>

// For the ReadLine method:
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

void ReadCircus(map<string, vector<string> > & circus) {
  while (cin){
    vector<string> v;
    ReadLine(v);
    string str = v[0];
    v.erase(v.begin());
    circus.insert(pair<string, vector<string> > (str, v));
  }
}

string Root(map<string, vector<string> > circus) {
  set<string> children;
  string aux;
  map<string, vector<string> >::iterator it_map;
  for (it_map = circus.begin(); it_map != circus.end(); it_map++) {
    for (int i = 2; i != it_map->second.size(); i++) {
      aux = it_map->second[i];
      if (aux[aux.length()-1] == ',') {
        aux = aux.substr(0, aux.length()-1);
      }
      children.insert(aux);
    }
  }
  for (it_map = circus.begin(); it_map != circus.end(); it_map++) {
    if (children.count(it_map->first) == 0) {
      return it_map->first;
    }
  }
  return "ERROR";
}

string UnbalancedWeight() {
  map<string, vector<string> > circus;
  ReadCircus(circus);
  //string Root = Root(circus);
  return Root(circus);
}

int main() {
  vector<string> v;
  cout << "\tSolucion: " << UnbalancedWeight() << endl;
}
