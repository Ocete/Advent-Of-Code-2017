#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>

#include <sstream>
#include <iomanip> // For the 'hex' in the stringstream

using namespace std;

void ReadASCIIVector(vector<int> & v) {
  string line;
  getline(cin, line);
  for (int i=0; i<line.length(); i++) {
    v.push_back(int(line[i]));
  }
}
////////////////////////////////////////////////////////////////////////////////
//                      Knot Hash
////////////////////////////////////////////////////////////////////////////////

void PrintList(const list<int> & l) {
  list<int>::const_iterator it;
  for (it = l.cbegin(); it != l.cend(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

void AdvanceIterator(list<int> & l, list<int>::iterator & it, int offset) {
  int i=0;
  while (i<offset) {
    it++;
    if (it == l.end()) {
      it = l.begin();
    }
    i++;
  }
}

// Reverse de elements [begin, end) from the list.
void Reverse(list<int> & l, list<int>::iterator begin, list<int>::iterator end) {
  stack<int> s;
  list<int>::iterator it = begin;
  while (it != end) {
    s.push(*it);
    it++;
    if (it == l.end()) it = l.begin();
  }
  it = begin;
  while (it != end) {
    *it = s.top();
    s.pop();
    it++;
    if (it == l.end()) it = l.begin();
  }
}

string HashToHex(vector<int> & dense_hash) {
  stringstream ss;
  for (int i=0; i<dense_hash.size(); i++) {
    ss << setfill('0') << setw(2) << hex << dense_hash[i];
  }
  return ss.str();
}

string KnotHash(vector<int> & lengths) {
  list<int> l;
  ;
  int skip_size = 0, size_of_list = 256, num_rounds = 64;
  list<int>::iterator current_pos, final_pos;

  for (int i=0; i<size_of_list; i++) {
    l.push_back(i);
  }
  current_pos = l.begin();
  lengths.push_back(17);
  lengths.push_back(31);
  lengths.push_back(73);
  lengths.push_back(47);
  lengths.push_back(23);

  //cout << "\n\tBefore the storm:" << endl;
  //PrintList(l);
  for (int j=0; j<num_rounds; j++) {
    for (int i=0; i<lengths.size(); i++) {
      if (lengths[i] > 0) {
        final_pos = current_pos;
        AdvanceIterator(l, final_pos, lengths[i]);
        Reverse(l, current_pos, final_pos);
      }
      AdvanceIterator(l, current_pos, lengths[i] + skip_size);
      skip_size++;

      //cout << "\n\tIteration:" << i << endl;
      //PrintList(l);
    }
  }

  // Calculate the dense hash
  current_pos = l.begin();
  int counter = 0, value;
  vector<int> dense_hash;
  while (current_pos != l.end()) {
    if (counter == 0) {
      value = *current_pos;
    } else {
      value ^= *current_pos;
    }
    counter++;
    current_pos++;
    if (counter == 16) {
      counter = 0;
      dense_hash.push_back(value);
    }
  }

  // Transform the hash into HEX
  string str = HashToHex(dense_hash);

  return str;
}
////////////////////////////////////////////////////////////////////////////////
string HexToBin(string str) {
  string result = "";
	for (int i = 0; i < str.length (); i++) {
		switch (str [i]) {
			case '0': result.append ("0000"); break;
			case '1': result.append ("0001"); break;
			case '2': result.append ("0010"); break;
			case '3': result.append ("0011"); break;
			case '4': result.append ("0100"); break;
			case '5': result.append ("0101"); break;
			case '6': result.append ("0110"); break;
			case '7': result.append ("0111"); break;
			case '8': result.append ("1000"); break;
			case '9': result.append ("1001"); break;
			case 'a': result.append ("1010"); break;
			case 'b': result.append ("1011"); break;
			case 'c': result.append ("1100"); break;
			case 'd': result.append ("1101"); break;
			case 'e': result.append ("1110"); break;
			case 'f': result.append ("1111"); break;
		}
	}
  return result;
}

void UpdateMap(vector<vector<bool> > & map, string str) {
  str = HexToBin(str);
  vector<bool> aux;
  for (int i=0; i<128; i++) {
    aux.push_back( '1' == str[i] );
  }
  map.push_back(aux);
}

void MarkIsland (vector<vector<bool> > & map, vector<vector<bool> > & map_in_progress, int i, int j) {
  map_in_progress[i][j] = true;
  if (i > 0 && map[i-1][j] && !map_in_progress[i-1][j])
    MarkIsland(map, map_in_progress, i-1, j);
  if (j > 0 && map[i][j-1] && !map_in_progress[i][j-1])
    MarkIsland(map, map_in_progress, i, j-1);
  if (i < 127 && map[i+1][j] && !map_in_progress[i+1][j])
    MarkIsland(map, map_in_progress, i+1, j);
  if (j < 127 && map[i][j+1] && !map_in_progress[i][j+1])
    MarkIsland(map, map_in_progress, i, j+1);
}

int CountIslands(vector<vector<bool> > & map) {
  vector<vector <bool> > map_in_progress;
  vector<bool> aux;
  int num_islands = 0;

  for (int i=0; i<128; i++) {
    aux.clear();
    for (int j=0; j<128; j++) {
      aux.push_back(false);
    }
    map_in_progress.push_back(aux);
  }

  for (int i=0; i<128; i++) {
    for (int j=0; j<128; j++) {
      if (map[i][j] && !map_in_progress[i][j]) {
        num_islands++;
        MarkIsland(map, map_in_progress, i, j);
      }
    }
  }

  return num_islands;
}

int DiskDefragmentation () {
  vector<int> raw_data, data;
  vector<vector<bool> > map;
  string str;
  int ones = 0;

  ReadASCIIVector(raw_data);
  raw_data.push_back( int('-') );

  for (int i=0; i<128; i++) {
    data = raw_data;
    str = to_string(i);
    for (int j=0; j<str.length(); j++)
      data.push_back( int(str[j]) );
    str = KnotHash(data);
    UpdateMap(map, str);
  }
  return CountIslands(map);
}


int main() {
  cout << "\tSolucion: " << DiskDefragmentation() << endl;
}
