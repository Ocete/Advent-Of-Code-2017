#include <iostream>
#include <set>
#include <string>
using namespace std;

int Passphrases() {
  set<string> S;
  bool safe;
  int num_good = 0;
  string str;
  do {
    S.clear();
    cin >> str;
    safe = true;
    while (str != "#" && str != "##") {
      if (S.count(str) == 0) {
        S.insert(str);
      } else {
        safe = false;
      }
      cin >> str;
    }
    if (safe) {
      num_good++;
    }
  } while (str != "##");
  return num_good;
}

int main() {
  cout << "\tSolucion: " << Passphrases() << endl;
}
