#include "main.h"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "WRONG ARGUMENTS NUMBER: " << argc;
    throw 1; // TODO: throw
  }
  init_bounds(); // set known bounds from bound.cpp
  list<RightPayload> matrices = read_list(argv[1]);
  int d = matrices.back().d;
  for (int i = 0; i < 10; i++) {
    matrices = step_matrices(matrices, d);
  }
}

