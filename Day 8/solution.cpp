#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>

// For the ReadLine method:
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

void PrintRegisters(const vector< vector<string> > & v){
  vector< vector<string> >::const_iterator it1;
  vector<string>::const_iterator it2;
  for (it1 = v.cbegin(); it1 != v.cend(); it1++) {
    for (it2 = it1->cbegin(); it2 != it1->cend(); it2++) {
      cout << " " << *it2;
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

void ReadRegisters(vector< vector<string> > & registers) {
  while (cin){
    vector<string> v;
    ReadLine(v);
    if (!v.empty()) {
      registers.push_back(v);
    }
  }
}

void Add(map<string, int> & m, string reg) {
  if (m.count(reg) == 0) {
    m.insert(pair<string, int> (reg, 0));
  }
}

int Max(map<string, int> m) {
  int max = numeric_limits<int>::min();
  map<string, int>::iterator it;
  for (it = m.begin(); it != m.end(); it++) {
    if (it->second > max) {
      max = it->second;
    }
  }
  return max;
}

int LargestRegister() {
  vector< vector<string> > registers;
  ReadRegisters(registers);
  //PrintRegisters(registers);

  map<string, int> map;
  vector< vector< string> >::iterator it;
  string reg_to_inc, reg_to_check, op;
  int value_to_inc, value_to_check;
  bool change_reg;
  for (it = registers.begin(); it != registers.end(); it++) {
    reg_to_inc = (*it)[0];
    value_to_inc = atoi ( ( (*it)[2] ).c_str() );
    if ( (*it)[1] == "dec" ) {
      value_to_inc = -1 * value_to_inc;
    }
    reg_to_check = (*it)[4];
    op = (*it)[5];
    value_to_check = atoi ( (*it)[6].c_str());

    Add(map, reg_to_inc);
    Add(map, reg_to_check);

    if (op == "==") {
        change_reg = map[reg_to_check] == value_to_check;
    } else if (op == "!=") {
        change_reg = map[reg_to_check] != value_to_check;
    } else if (op == ">=") {
        change_reg = map[reg_to_check] >= value_to_check;
    } else if (op == "<=") {
        change_reg = map[reg_to_check] <= value_to_check;
    } else if (op == ">") {
        change_reg = map[reg_to_check] > value_to_check;
    } else if (op == "<") {
        change_reg = map[reg_to_check] < value_to_check;
    } else {
      cout << "This should never appear" << endl;
    }

    if (change_reg) {
      map[reg_to_inc] += value_to_inc;
    }
  }

  return Max(map);
}

int main() {
  vector<string> v;
  cout << "\tSolucion: " << LargestRegister() << endl;
}
