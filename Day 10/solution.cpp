#include <iostream>
#include <list>
#include <vector>
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

int Position(list<int> & l, list<int>::iterator & it) {
  int pos = 0;
  list<int>::iterator it_aux = l.begin();
  while (it_aux != it) {
    it_aux++;
    pos++;
  }
  return pos;
}

void Rotate(list<int> & l) {
  int aux = *( l.begin() );
  l.pop_front();
  l.push_back(aux);
}


int KnotHash() {
  list<int> l, aux_list;
  vector<int> lengths;
  int skip_size = 0, size_of_list = 5;
  list<int>::iterator current_pos, final_pos, it_aux;

  for (int i=0; i<size_of_list; i++) {
    l.push_back(i);
  }
  current_pos = l.begin();
  ReadVector(lengths);

  cout << "\n\tBefore the storm:" << endl;
  PrintList(l);
  for (int i=0; i<lengths.size(); i++) {
    if (lengths[i] == size_of_list) {
      int i_objetive = Position(l, current_pos) - 1, i_current_pos;
      final_pos = current_pos;
      AdvanceIterator(l, final_pos, 1);
      // Insert every element but the first one
      aux_list.splice(aux_list.begin(), l, final_pos, current_pos );

      aux_list.reverse();
      l.splice(current_pos, aux_list);

      i_current_pos = Position(l, current_pos);
      while (i_objetive != i_current_pos) {
        Rotate(l);
        i_current_pos = (i_current_pos - 1) % size_of_list;
      }

      // Advance current_pos
      AdvanceIterator(l, current_pos, skip_size+1);
    } else {
      final_pos = current_pos;
      AdvanceIterator(l, final_pos, lengths[i]);
      aux_list.splice( aux_list.begin(), l, current_pos, final_pos );
      aux_list.reverse();
      l.splice(final_pos, aux_list);

      // Advance current_pos
      current_pos = final_pos;
      AdvanceIterator(l, current_pos, skip_size);
    }
    skip_size++;

      cout << "\n\tIteration:" << i << endl;
      PrintList(l);
  }
  current_pos = l.begin();
  final_pos = current_pos;
  final_pos++;
  return (*current_pos) * ( *final_pos);
}

int main() {
  cout << "\tSolucion: " << KnotHash() << endl;
}
