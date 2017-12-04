#include <iostream>
#include <vector>
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
  int checksum = 0, num, i;
  bool found;
  vector<int> v;
  do {
    v.clear();
    num = read();
    found = false;
    while (num != -1 && num != -2) {
      if (!v.empty()) {
        i = 0;
        while (!found && i < v.size()) {
          if ( num % v[i] == 0) {
            checksum += num / v[i];
            found = true;
          } else if (v[i] % num == 0 ) {
            checksum += v[i] / num;
            found = true;
          }
          i++;
        }
      }
      v.push_back(num);
      num = read();
    }
  } while (num != -2);
  return checksum;
}

int main() {
  cout << chekSum() << endl;
}
