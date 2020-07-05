#include "main.h"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2 || !is_positive_int(argv[1])) { // check d (first is program name itself)
    cout << argc << " " << argv[1];
    cout << "WRONG ARGUMENTS";
    throw 1; // TODO: throw
  }
  // convert d to int
  int d = atoi(argv[1]);
  init_bounds(); // set known bounds from bound.cpp
  RightPayload m = init_matrix(d); // create base matrix payload
  cout << "m(" << m.cols + 1 << ") =\n";
  m.print();
  int n = d;
  int k = 1;
  list<RightPayload> matrices{ m };
  // make 10 steps
  list<strategy_step> strategy;
  for (int i = 0; i < 10; i++) {
    strategy.push_back(strategy_step(1, 1, 1));
  }
  //strategy.push_back(strategy_step(2, 1000, 5));
  list<strategy_step>::iterator it = strategy.begin();
  for (int i = 0; i < 10; i++, ++it) {
    matrices = step_matrices(matrices, *it, d);
  }
}

RightPayload init_matrix(int d) {
  long long x = (1LL << (d - 1)) - 1;
  // fill matrix with ones
  set<long long> new_set;
  new_set.insert(x);
  return RightPayload(new_set, 1, d - 1, d);
}

// positive int check (copied from stackoverflow 'cause nowhere to be found)
inline bool is_positive_int(const char *argv) {
  if (argv[0] == 0 || argv[0] == '-' || ((!isdigit(argv[0])) && (argv[0] != '+'))) return false;

  char * p;
  strtol(argv, &p, 10);

  return (*p == 0);
}

