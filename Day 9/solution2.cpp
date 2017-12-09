#include <iostream>
using namespace std;

int StreamProcessing() {
  int garbage = 0;
  bool basura = false;
  char car;

  while(cin) {
    cin >> car;
    if (basura) {
      if (car == '!') {
        cin >> car;
      } else if (car == '>') {
        basura = false;
      } else {
        garbage++;
      }
    } else {
      if (car == '<') {
        basura = true;
      }
    }
  }
  return garbage;
}

int main() {
  cout << "\tSolucion: " << StreamProcessing() << endl;
}
