#include <iostream>
#include <set>
#include <string>
#include <limits>
#include <vector>
using namespace std;

void ReadVector(vector<int> & v, int to_read) {
  v.clear();
  int num;
  for (int i=0; i<to_read; i++) {
    cin >> num;
    v.push_back(num);
  }
}

void Max(const vector<int> & v, int &pos, int &value) {
  value = numeric_limits<int>::min();
  pos = -1;
  for (int i=0; i<v.size(); i++) {
    if (v[i] > value) {
      value = v[i];
      pos = i;
    }
  }
}

void Reallocate(vector<int> & banks) {
  int max, pos_max;
  Max(banks, pos_max, max);
  banks[pos_max] = 0;
  int i = (pos_max+1) % banks.size();
  while (max > 0) {
    banks[i]++;
    max--;
    i = (i+1) % banks.size();
  }
}

bool CheckConfiguration(vector<int> v, set<string> & configurations) {
  string str = "";
  for (int i = 0; i<v.size(); i++) {
    str += " " + to_string(v[i]);
  }
  cout << str << endl;
  if (configurations.count(str) > 0) {
    return false;
  } else {
    configurations.insert(str);
    return true;
  }
}

int MemoryReallocation() {
  int num_reallocations = 0, NUM_BANKS = 16;
  vector<int> banks;
  set<string> configurations;
  ReadVector(banks, NUM_BANKS);
  CheckConfiguration(banks, configurations);
  do {
    num_reallocations++;
    Reallocate(banks);
  } while (CheckConfiguration(banks, configurations));
  return num_reallocations;
}

int main() {
  cout << "\tSolucion: " << MemoryReallocation() << endl;
}
