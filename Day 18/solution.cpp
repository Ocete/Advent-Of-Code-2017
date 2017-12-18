#include <iostream>
#include <vector>

using namespace std;

void ReadCode (vector<vector<string> > & data) {
  data.clear();
  string str;

  cin >> str;
  while (cin) {
    vector<string> new_line;
    new_line.push_back(str);
    cin >> str;
    new_line.push_back(str);
    if (str == "snd" || str == "rcv" ){
        cin >> str;
        new_line.push_back(str);
    }
    data.push_back(new_line);
    cin >> str;
  }
}

void PrintCode(vector<vector<string> > & data) {
  for (vector<vector<string> >::iterator it1 = data.begin(); it1!=data.end(); it1++){
    for (vector<string>::iterator it2=(*it1).begin(); it2!=(*it1).end(); it2++) {
      cout << *it2 << " ";
    }
    cout << endl;
  }
}

int ctoi(char c) {
  return c - 'a';
}

int RegisterToInt(vector<int> registers, string r) {
  if (r[0] >= 'a' && r[0] <= 'z')
    return registers[ ctoi(r[0]) ];
  else
    return atoi( r.c_str() );
}

bool Operation(vector<vector<string> > & data, vector<int> & registers,
      int & PC, int & last_snd) {
  string op = data[PC][0];
  if (op == "add") {
    registers[ctoi( data[PC][1][0] )] += RegisterToInt(registers, data[PC][2]);
    PC++;
  } else if (op == "mul") {
    registers[ctoi( data[PC][1][0] )] *= RegisterToInt(registers, data[PC][2]);
    PC++;
  } else if (op == "mod") {
    registers[ctoi( data[PC][1][0] )] %= RegisterToInt(registers, data[PC][2]);
    PC++;
  } else if (op == "set") {
    cout << "hey" << endl;
    registers[ctoi( data[PC][1][0] )] = RegisterToInt(registers, data[PC][2]);
    PC++;
  } else if (op == "snd") {
    last_snd = RegisterToInt(registers, data[PC][1]);
    PC++;
  } else if (op == "rcv") {
    if ( RegisterToInt(registers, data[PC][1]) != 0) {
      return true;
    }
  } else if (op == "jgz") {
    if ( RegisterToInt(registers, data[PC][1]) > 0) {
      PC += RegisterToInt(registers, data[PC][2]);
    } else {
      PC++;
    }
  }
  return false;
}

int Duet() {
  vector<vector<string> > data;
  vector<int> registers;
  int PC = 0, last_snd;

  ReadCode(data);
  PrintCode(data);

  for (char c='a'; c<='z'; c++) {
    registers.push_back(0);
  }
  while ( !Operation(data, registers, PC, last_snd) );

  return last_snd;
}


int main() {
  cout << "\tSolucion: " << Duet() << endl;
}
