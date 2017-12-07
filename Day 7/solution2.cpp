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

struct Tree{
  int weight;
  vector<Tree*> children;
};

void PrintMap(map<string, vector<string> > m){
  map<string, vector<string> >::iterator it_map;
  vector<string>::iterator it;
  for (it_map = m.begin(); it_map != m.end(); it_map++) {
    cout << it_map->first;
    for (it=it_map->second.begin(); it != it_map->second.end(); it++) {
      cout << " " << *it;
    }
    cout << endl;
  }
}

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
    if (!v.empty()) {
      string str = v[0];
      v.erase(v.begin());
      for (int i = 0; i < v.size(); i++) {
        if (v[i][v[i].length()-1] == ',') {
          v[i] = v[i].substr(0, v[i].length()-1);
        }
      }
      circus.insert(pair<string, vector<string> > (str, v));
    }
  }
}

string Root(const map<string, vector<string> > & circus) {
  set<string> children;
  string aux;
  map<string, vector<string> >::const_iterator it_map;
  for (it_map = circus.cbegin(); it_map != circus.cend(); it_map++) {
    for (int i = 2; i < it_map->second.size(); i++) {
      children.insert(it_map->second[i]);
    }
  }
  for (it_map = circus.begin(); it_map != circus.end(); it_map++) {
    if (children.count(it_map->first) == 0) {
      return it_map->first;
    }
  }
  return "ERROR";
}

void BuildTree(Tree * tree, const map<string, vector<string> > & circus, const string & node) {
  tree = new Tree;
  vector<string> data = circus[node];
  tree->weight = atoi( ( data[0].substr(1, data[0].length()-1) ).c_str() );
  for (int i=2; i<data.size(); i++) {
    Tree * aux;
    BuildTree(aux, circus, data[i]);
    tree->children.push_back(aux);
  }
}

string UnbalancedWeight() {
  map<string, vector<string> > circus;
  Tree * tree;
  ReadCircus(circus);
  string root = Root(circus);
  BuildTree(tree, circus, root);
  return root;
}

int main() {
  vector<string> v;
  cout << "\tSolucion: " << UnbalancedWeight() << endl;
}
