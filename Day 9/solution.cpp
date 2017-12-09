#include <iostream>
using namespace std;

int StreamProcessing() {
  int result = 0, depth_level = 0;
  bool basura = false;
  char car;

  while(cin) {
    cin >> car;
    if (basura) {
      if (car == '!') {
        cin >> car;
      } else if (car == '>') {
        basura = false;
      }
    } else {
      if (car == '{') {
        depth_level++;
      } else if (car == '}') {
        result += depth_level;
        depth_level--;
      } else if (car == '<') {
        basura = true;
      }
    }
  }
  return result;
}

int main() {
  cout << "\tSolucion: " << StreamProcessing() << endl;
}
