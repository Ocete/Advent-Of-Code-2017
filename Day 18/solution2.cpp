#include <iostream>
#include <vector>
#include <list>

using namespace std;

void ReadCode (vector<vector<string> > & code) {
  code.clear();
  string str;

  cin >> str;
  while (cin) {
    vector<string> new_line;
    new_line.push_back(str);
    if (str != "snd" && str != "rcv" ){
        cin >> str;
        new_line.push_back(str);
    }
    cin >> str;
    new_line.push_back(str);
    code.push_back(new_line);
    cin >> str;
  }
}

void PrintCode(vector<vector<string> > & code) {
  for (vector<vector<string> >::iterator it1 = code.begin(); it1!=code.end(); it1++){
    for (vector<string>::iterator it2=(*it1).begin(); it2!=(*it1).end(); it2++) {
      cout << *it2 << " ";
    }
    cout << endl;
  }
}

int ctoi(char c) {
  return c - 'a';
}

void PrintRegisters(const vector<long long unsigned> & registers) {
  for (char c='a'; c<='z'; c++) {
    cout << c << " -> " << registers[ctoi(c)] << endl;
  }
}

int RegisterToInt(vector<long long unsigned> registers, string r) {
  if (r[0] >= 'a' && r[0] <= 'z')
    return registers[ ctoi(r[0]) ];
  else
    return atoi( r.c_str() );
}

void Operation(const vector<vector<string> > & code, vector<long long unsigned> & registers,
      int & PC, list<long long unsigned> & my_queue, list<long long unsigned> & other_queue,
      bool & i_stopped, bool & other_stopped, unsigned & num_sent) {
  string op = code[PC][0];
  if (op == "add") {
    registers[ctoi( code[PC][1][0] )] += RegisterToInt(registers, code[PC][2]);
    PC++;
  } else if (op == "mul") {
    registers[ctoi( code[PC][1][0] )] *= RegisterToInt(registers, code[PC][2]);
    PC++;
  } else if (op == "mod") {
    registers[ctoi( code[PC][1][0] )] %= RegisterToInt(registers, code[PC][2]);
    PC++;
  } else if (op == "set") {
    registers[ctoi( code[PC][1][0] )] = RegisterToInt(registers, code[PC][2]);
    PC++;
  } else if (op == "snd") {
    other_queue.push_back( RegisterToInt(registers, code[PC][1]) );
    other_stopped = false;
    PC++;
    num_sent++;
  } else if (op == "rcv") {
    if ( my_queue.empty() ) {
      i_stopped = true;
    } else {
      registers[ctoi( code[PC][1][0] )] = my_queue.front();
      my_queue.pop_front();
      PC++;
    }
  } else if (op == "jgz") {
    if ( RegisterToInt(registers, code[PC][1]) > 0) {
      PC += RegisterToInt(registers, code[PC][2]);
    } else {
      PC++;
    }
  } else {
    cout << "This shoud never appear" << endl;
  }
}

int Duet() {
  vector<vector<string> > code;
  vector<long long unsigned> registers0, registers1;
  list<long long unsigned> queue0, queue1;
  int PC0 = 0, PC1 = 0;
  unsigned num_sent0 = 0, num_sent1 = 0;
  bool stopped0 = false, stopped1 = false;

  ReadCode(code);
  //PrintCode(code);

  for (char c='a'; c<='z'; c++) {
    registers0.push_back(0);
    if (c == 'p')
      registers1.push_back(1);
    else
      registers1.push_back(0);
  }

  while ( !stopped0 || !stopped1 ) {
    if (!stopped0) {
      Operation (code, registers0, PC0, queue0, queue1, stopped0, stopped1, num_sent0);
    } else {
      Operation (code, registers1, PC1, queue1, queue0, stopped1, stopped0, num_sent1);
    }
  }

  //PrintRegisters(registers0);
  //PrintRegisters(registers1);

  return num_sent1;
}


int main() {
  cout << "\tSolucion: " << Duet() << endl;
}
