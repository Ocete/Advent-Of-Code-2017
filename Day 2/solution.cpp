#include <iostream>
#include <limits>
using namespace std;

int read() {
  string str;
  cin >> str;
  if (str == "#") {
    return -1;
  } else if (str == "##") {
    return -2;
  } else {
    return atoi(str.c_str());
  }
}

int chekSum() {
  int checksum = 0, max, min, num;
  do {
    max = numeric_limits<int>::min();
    min = numeric_limits<int>::max();
    num = read();
    while (num != -1 && num != -2) {
      min = num < min ? num : min;
      max = num > max ? num : max;
      num = read();
    }
    checksum += max - min;
  } while (num != -2);
  return checksum;
}

int main() {
  cout << chekSum() << endl;
}
