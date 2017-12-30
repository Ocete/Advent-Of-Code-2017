#include <iostream>
#include <vector>
#include <limits>

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

void AdvanceTime (vector<particle> & swarm) {
  vector<int> to_erase;
  for (int i=0; i<swarm.size(); i++) {
    for (int j=0; j<3; j++) {
      swarm[i].vel[j] += swarm[i].ac[j];
      swarm[i].pos[j] += swarm[i].vel[j];
    }
    to_erase.clear();
    for (int j=0; j<i; j++) {
      if ( swarm[i].pos[0] == swarm[j].pos[0] &&
           swarm[i].pos[1] == swarm[j].pos[1] &&
           swarm[i].pos[2] == swarm[j].pos[2]) {
        to_erase.push_back(j);
      }
    }
    if (!to_erase.empty())
      to_erase.push_back(i);
    for (int j=to_erase.size()-1; j>=0; j--) {
      swarm.erase(swarm.begin() + to_erase[j]);
    }
  }
}

int ParticleSwarm() {
  vector<particle> swarm;

  ReadSwarm(swarm);
  for (int i=0; i<1000000; i++)
    AdvanceTime(swarm);

  return swarm.size();
}


int main() {
  cout << "\tSolucion: " << ParticleSwarm() << endl;
}
