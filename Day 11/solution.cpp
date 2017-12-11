#include <iostream>
#include <string>
using namespace std;

string GetMove() {
  string str;
  getline(cin, str, ',');
  if (str[str.size()-1] == '\n')
    str = str.substr(0,str.size()-1);
  return str;
}

void Move(pair<int, int> & p, string str) {
  if (str == "n") {
    p.first += 2;
  } else if (str == "nw") {
    p.first++;
    p.second--;
  } else if (str == "ne") {
    p.first++;
    p.second++;
  } else if (str == "s") {
    p.first -= 2;
  } else if (str == "sw") {
    p.first--;
    p.second--;
  } else if (str == "se") {
    p.first--;
    p.second++;
  } else {
    cout << "This should never appear: " << str << '-' << endl;
  }
}

int Dist(pair<int,int> & p) {
  return abs(p.second) + abs( abs(p.first) - abs(p.second) ) / 2;
}

int HexPath() {
  pair<int, int> current_pos (0,0);
  string str;
  str = GetMove();
  while (cin) {
    Move(current_pos, str);
    str = GetMove();
  }
  return Dist(current_pos);
}

int main() {
  cout << "\tSolucion: " << HexPath() << endl;
}
