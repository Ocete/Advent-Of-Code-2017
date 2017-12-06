#include <iostream>
#include <map>
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

// Returns -1 if the configuration hasn't been seen yet and a positive integer
//  with the number of cycles between both appearances in the other case
int CheckConfiguration(vector<int> v, map<string, int> & configurations, int num_reallocations) {
  string str = "";
  for (int i = 0; i<v.size(); i++) {
    str += " " + to_string(v[i]);
  }
  cout << str << endl;
  if (configurations.count(str) > 0) {
    return num_reallocations - configurations[str];
  } else {
    configurations.insert(pair<string, int> (str, num_reallocations));
    return -1;
  }
}

int MemoryReallocation() {
  int num_reallocations = 0, NUM_BANKS = 16, max, pos_max, result;
  vector<int> banks;
  map<string, int> configurations;
  ReadVector(banks, NUM_BANKS);
  CheckConfiguration(banks, configurations, num_reallocations);
  do {
    num_reallocations++;
    Reallocate(banks);
    result = CheckConfiguration(banks, configurations, num_reallocations);
  } while (result == -1);
  return result;
}

int main() {
  cout << "\tSolucion: " << MemoryReallocation() << endl;
}
