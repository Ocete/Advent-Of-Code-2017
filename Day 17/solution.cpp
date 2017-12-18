#include <iostream>
#include <list>

using namespace std;

int Spinlock() {
  list<int> l;
  list<int>::iterator it;
  int cont = 0, jump;

  cin >> jump;
  l.push_back(0);
  it = l.begin();

  for (int i=1; i<=2017; i++) {
    for (int j=0; j<jump +1; j++) {
      it++;
      if (it == l.end())
        it = l.begin();
    }
    l.insert(it, i);
    it--;
  }

  it++;
  return *it;
}


int main() {
  cout << "\tSolucion: " << Spinlock() << endl;
}
