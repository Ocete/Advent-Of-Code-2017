#include <iostream>
#include <string>
#include <set>

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

void ReadData(vector< vector<string> > & data) {
  while (cin){
    vector<string> v;
    ReadLine(v);
    if (!v.empty()) {
      data.push_back(v);
    }
  }
}

int DigitalPlumber() {
  vector<vector<string> > data;
  vector<bool> already_added;
  set<int> s;
  int i=0;
  bool keep_changing = false;

  ReadData(data);
  for (int i=0; i<data.size(); i++) {
    already_added.push_back(0);
  }

  s.insert(0);
  while( i < data.size() ) {
    if (!already_added[i] && s.count( atoi(data[i][0].c_str()) ) > 0) {
      for (int j=2; j<data[i].size(); j++) {
        s.insert( atoi( data[i][j].c_str() ) );
        keep_changing = true;
        already_added[i] = true;
      }
    }
    i++;
    if (i==data.size() && keep_changing) {
      keep_changing = false;
      i=0;
    }
  }
  return s.size();
}

int main() {
  cout << "\tSolucion: " << DigitalPlumber() << endl;
}
