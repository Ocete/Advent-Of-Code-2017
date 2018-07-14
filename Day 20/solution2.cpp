#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

struct particle {
  vector<int> pos;
  vector<int> vel;
  vector<int> ac;
};

void ReadTrash(int num) {
  char c;
  for (int i=0; i<num; i++)
    cin >> c;
}

void ReadSwarm (vector<particle> & swarm) {
  swarm.clear();
  char c;
  int int_read;

  cin >> c;
  while (cin) {
    particle p;

    ReadTrash(2);
    for (int i=0; i<3; i++) {
      cin >> int_read;
      p.pos.push_back(int_read);
      cin >> c;
    }
    ReadTrash(4);
    for (int i=0; i<3; i++) {
      cin >> int_read;
      p.vel.push_back(int_read);
      cin >> c;
    }
    ReadTrash(4);
    for (int i=0; i<3; i++) {
      cin >> int_read;
      p.ac.push_back(int_read);
      cin >> c;
    }
    swarm.push_back(p);
    cin >> c;
  }
}

struct comp {
  bool operator() (const vector<int> &v1, const vector<int> &v2) const {
    return v1[0] > v2[0] || (v1[0] == v2[0] && v1[1] > v2[1]) ||
          (v1[0] == v2[0] && v1[1] == v2[1] && v1[2] > v2[2]);
  }
};

void AdvanceTime (vector<particle> & swarm) {
  map<vector<int>, int, comp> positions;
  map<vector<int>, int>::iterator it;
  vector<int> to_erase;

  for (int i=0; i<swarm.size(); i++) {
    // Move particle
    for (int j=0; j<3; j++) {
      swarm[i].vel[j] += swarm[i].ac[j];
      swarm[i].pos[j] += swarm[i].vel[j];
    }

    // Check collisions
    it = positions.find(swarm[i].pos);

    if (it != positions.end()) {
      to_erase.push_back(i);
      if (it->second != -1) {
        to_erase.push_back(it->second);
        it->second = -1;
      }
    } else {
      positions[ swarm[i].pos ] = i;
    }
  }

  // Delete collisions
  if (!to_erase.empty()) {
    sort(to_erase.begin(), to_erase.end());
    for (int j=to_erase.size()-1; j>=0; j--) {
      swarm.erase(swarm.begin() + to_erase[j]);
    }
  }
}

int ParticleSwarm() {
  vector<particle> swarm;

  ReadSwarm(swarm);
  for (int i=0; i<10000; i++)
    AdvanceTime(swarm);

  return swarm.size();
}


int main() {
  cout << "\tSolucion: " << ParticleSwarm() << endl;
}
