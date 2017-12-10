#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

void ReadVector(vector<int> & v) {
  int num;
  cin >> num;
  while (cin) {
    v.push_back(num);
    cin >> num;
  }
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

int KnotHash() {
  list<int> l;
  vector<int> lengths;
  int skip_size = 0, size_of_list = 256;
  list<int>::iterator current_pos, final_pos;

  for (int i=0; i<size_of_list; i++) {
    l.push_back(i);
  }
  current_pos = l.begin();
  ReadVector(lengths);

  //cout << "\n\tBefore the storm:" << endl;
  //PrintList(l);

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
  current_pos = l.begin();
  final_pos = current_pos;
  final_pos++;
  return (*current_pos) * ( *final_pos);
}

int main() {
  cout << "\tSolucion: " << KnotHash() << endl;
}
