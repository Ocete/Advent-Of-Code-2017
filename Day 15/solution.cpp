#include <iostream>
#include <bitset>

using namespace std;

unsigned long long Generator(const unsigned factor, unsigned long long & prev) {
  prev = (factor * prev ) % 2147483647;
  return prev;
}

int DuelingGenerators() {
  long long int MAX = 40000000, count = 0;
  string gen1, gen2;
  const unsigned factor1 = 16807, factor2 = 48271;
  unsigned long long prev1 = 289, prev2 = 629;

  for (long long int i=0; i<MAX; i++) {
    gen1 = bitset<32>( Generator(factor1, prev1) ).to_string();
    gen2 = bitset<32>( Generator(factor2, prev2) ).to_string();
    //cout << prev1<< endl << prev2<<endl <<endl;
    if ( gen1.substr(16,31) == gen2.substr(16,31) ) {
      count++;
    }
  }

  return count;
}


int main() {
  cout << "\tSolucion: " << DuelingGenerators() << endl;
}
