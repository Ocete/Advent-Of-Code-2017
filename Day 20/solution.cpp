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

double Acceleration (const particle & p, int time) {
  double ac = 0;

  for (int i=0; i<3; i++) {
    //ac += abs( p.pos[i] + p.vel[i] * time + p.ac[i]*time*(time+1)/2 );
    ac += abs( p.ac[i] );
  }

  return ac;
}

int ParticleSwarm() {
  vector<particle> swarm;
  int i_min;
  double min_ac = numeric_limits<double>::max(), aux_ac, time = 5000000;

  ReadSwarm(swarm);
  for (int i=0; i<swarm.size(); i++) {
    aux_ac = Acceleration(swarm[i], time);
    if (aux_ac == min_ac) {
      cout << "The ACs match " << i << " " << i_min << endl;
    } else if (aux_ac < min_ac) {
      min_ac = aux_ac;
      i_min = i;
    }
  }

  return i_min;
}


int main() {
  cout << "\n We can solve this problem by loking only at the AC. The answer will";
  cout << " be the particle with the least AC. If 2 ACs match just look at the";
  cout << " one with the least velocity from those 2 (or just try if there are few options left)" << endl << endl;

  cout << "\tSolucion: " << ParticleSwarm() << endl;
}
