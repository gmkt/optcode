#pragma once
#include <map>
#include <set>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#define MAXBUFSIZE 1000000
using namespace std;

class RightPayload {
public:

  set<long long> codewords;
  int rows, cols, d;

  RightPayload(set<long long>& codewords, int rows, int cols, int d);
  void add_word(long long word);
  void print();
private:
};

class strategy_step {
public:
  int k_step;
  long long msize, dist;
  // msize - average size of each bucket
  // dist - distance within bucket
  strategy_step(int k_step, long long msize, long long dist) {
    this->k_step = k_step;
    this->msize = msize;
    this->dist = dist;
  }
private:
};

struct my_arr {
  long long* arr;
  int size;
  my_arr(long long* arr, int size) {
    this->arr = arr;
    this->size = size;
  }
};

list<my_arr> get_potential_leaders(const my_arr& H, int r, strategy_step st, int d);
RightPayload add_leaders_to_system_payload(const RightPayload& payload, const my_arr& leaders);
my_arr get_H_matrix(const RightPayload& p);
bool check_matrix(set<set<long long>>& print_set, set<map<int, int>>& map_set, const RightPayload& p, int d, bool easy_criteria);
list<RightPayload> read_list(const char* filename);
