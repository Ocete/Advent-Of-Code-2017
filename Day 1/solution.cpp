#include <iostream>
using namespace std;

int ctoi(char c) {
  return c - '0';
}

long long int InverseCaptcha() {
  string str;
  cin >> str;
  long long int sum = 0, tope = str.length()-1;
  if (str[0] == str[tope])
    sum += ctoi(str[0]);
  for (int i=0; i<tope; i++) {
    if (str[i] == str[i+1])
      sum += ctoi(str[i]);
  }
  return sum;
}

int main() {
  cout << InverseCaptcha() << endl;
}
