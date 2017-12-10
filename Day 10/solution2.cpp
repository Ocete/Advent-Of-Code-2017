#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

#include <iomanip> // For the 'hex' in the stringstream
using namespace std;

void ReadASCIIVector(vector<int> & v) {
  string line;
  getline(cin, line);
  for (int i=0; i<line.length(); i++) {
    v.push_back(int(line[i]));
  }
  v.push_back(17);
  v.push_back(31);
  v.push_back(73);
  v.push_back(47);
  v.push_back(23);
}

void PrintList(const list<int> & l) {
  list<int>::const_iterator it;
  for (it = l.cbegin(); it != l.cend(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

void AdvanceIterator(list<int> & l, list<int>::iterator & it, int offset) {
  int i=0;
  while (i<offset) {
    it++;
    if (it == l.end()) {
      it = l.begin();
    }
    i++;
  }
}

// Reverse de elements [begin, end) from the list.
void Reverse(list<int> & l, list<int>::iterator begin, list<int>::iterator end) {
  stack<int> s;
  list<int>::iterator it = begin;
  while (it != end) {
    s.push(*it);
    it++;
    if (it == l.end()) it = l.begin();
  }
  it = begin;
  while (it != end) {
    *it = s.top();
    s.pop();
    it++;
    if (it == l.end()) it = l.begin();
  }
}

string HashToHex(vector<int> & dense_hash) {
  stringstream ss;
  for (int i=0; i<dense_hash.size(); i++) {
    ss << setfill('0') << setw(2) << hex << dense_hash[i];
  }
  return ss.str();
}

string KnotHash() {
  list<int> l;
  vector<int> lengths;
  int skip_size = 0, size_of_list = 256, num_rounds = 64;
  list<int>::iterator current_pos, final_pos;

  for (int i=0; i<size_of_list; i++) {
    l.push_back(i);
  }
  current_pos = l.begin();
  ReadASCIIVector(lengths);

  //cout << "\n\tBefore the storm:" << endl;
  //PrintList(l);
  for (int j=0; j<num_rounds; j++) {
    for (int i=0; i<lengths.size(); i++) {
      if (lengths[i] > 0) {
        final_pos = current_pos;
        AdvanceIterator(l, final_pos, lengths[i]);
        Reverse(l, current_pos, final_pos);
      }
      AdvanceIterator(l, current_pos, lengths[i] + skip_size);
      skip_size++;

      //cout << "\n\tIteration:" << i << endl;
      //PrintList(l);
    }
  }

  // Calculate the dense hash
  current_pos = l.begin();
  int counter = 0, value;
  vector<int> dense_hash;
  while (current_pos != l.end()) {
    if (counter == 0) {
      value = *current_pos;
    } else {
      value ^= *current_pos;
    }
    counter++;
    current_pos++;
    if (counter == 16) {
      counter = 0;
      dense_hash.push_back(value);
    }
  }

  // Transform the hash into HEX
  string str = HashToHex(dense_hash);

  return str;
}

int main() {
  cout << "\tSolucion: " << KnotHash() << endl;
}
