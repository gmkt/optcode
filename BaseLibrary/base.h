#pragma once
#include <map>
#include <set>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#define MAXBUFSIZE 1000000
using namespace std;

class RightPayload {
public:

  set<long long> codewords;
  int rows, cols, d;

  RightPayload(set<long long> codewords, int rows, int cols, int d);
  void add_word(long long word);
  void print();
private:
};

list<set<long long>> get_potential_leaders(vector<long long> H, RightPayload payload, int d);
RightPayload add_leaders_to_system_payload(RightPayload payload, set<long long> leaders);
vector<long long> get_H_matrix(RightPayload p);
//bool update_print_set(set<map<int, vector<long long>>>&, RightPayload);
bool update_print_set(set<map<int, int>>&, RightPayload, int);
list<RightPayload> read_list(const char* filename);
