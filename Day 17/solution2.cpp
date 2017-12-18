/*
  You can solve this problem by not building the list and using the mod.
  By keeping the number of elements in the list (just an integrer) and checking
  if within each iteration you hit the last value of the list, inserting a new
  element before 0 (updating that value).
*/

#include <iostream>
#include <list>

using namespace std;

int Spinlock() {
  list<int> l;
  list<int>::iterator it, it_0;
  int cont = 0, jump;

  cin >> jump;
  l.push_back(0);
  it = l.begin();
  it_0 = it;

  for (long long unsigned i=1; i<=50000000; i++) {
    for (int j=0; j<jump +1; j++) {
      it++;
      if (it == l.end())
        it = l.begin();
    }
    l.insert(it, i);
    it--;
  }

  it_0++;
  if (it_0 == l.end())
    it_0 = l.begin();
  return *it_0;
}


int main() {
  cout << "\tSolucion: " << Spinlock() << endl;
}
