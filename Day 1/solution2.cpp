#include <iostream>
using namespace std;

int ctoi(char c) {
  return c - '0';
}

long long int InverseCaptcha() {
  string str;
  cin >> str;
  long long int sum = 0, jump = str.length()/2, j=jump;
  for (int i=0; i<jump; i++) {
    if ( str[i] == str[j] )
      sum += ctoi(str[i]);
    j++;
  }
  return 2*sum;
}

int main() {
  cout << InverseCaptcha() << endl;
}
