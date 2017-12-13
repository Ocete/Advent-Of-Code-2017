#include <iostream>
#include <map>

using namespace std;

// For the input to be read correctly there must be no ':' between numbers.
// Returns the last layer
int ReadFirewall(map<int, int> & firewall, map<int, int> & current_positions, map<int, bool> & going_forward) {
  int pos, last_layer;
  cin >> pos;
  while (cin) {
    cin >> firewall[pos];
    current_positions[pos] = 0;
    going_forward[pos] = true;
    last_layer = pos;
    cin >> pos;
  }
  return last_layer;
}

template <class T>
void PrintMap(map<int, T> & m) {
  for (typename map<int, T>::iterator it = m.begin(); it != m.end(); it++) {
    cout << it->first << ": " << it->second << endl;
  }

}

void Scan(map<int, int> & firewall, map<int, int> & current_positions, map<int, bool> & going_forward) {
  map<int, int>::iterator it;
  int pos;
  for (it = current_positions.begin(); it != current_positions.end(); it++) {
    pos = it->first;
    if (going_forward[pos]) {
      it->second++;
    } else {
      it->second--;
    }
    if (it->second == 0 || it->second == (firewall[pos] - 1) ) {
      going_forward[pos] = !going_forward[pos];
    }
  }
}

int Delay() {
  map<int, int> firewall;
  map<int, int> current_positions, delayed_positions;
  map<int, bool> going_forward, delayed_goind_forward;
  int paquet_layer = -1, last_layer, delay = 0;
  bool passed;

  last_layer = ReadFirewall(firewall, delayed_positions, delayed_goind_forward);
  //PrintMap(firewall);
  //PrintMap(current_positions);
  //PrintMap(going_forward);

  do {
    paquet_layer = -1;
    passed = true;
    current_positions = delayed_positions;
    going_forward = delayed_goind_forward;

    while (paquet_layer <= last_layer && passed) {
      paquet_layer++;
      if (firewall.count(paquet_layer) > 0 && current_positions[paquet_layer] == 0) {
        passed = false;
      }
      if (passed) {
        Scan(firewall, current_positions, going_forward);
      }
    }

    if (!passed) {
      delay++;
      Scan(firewall, delayed_positions, delayed_goind_forward);
    }
  } while (!passed);

  return delay;
}

int main() {
  cout << "\tSolucion: " << Delay() << endl;
}
