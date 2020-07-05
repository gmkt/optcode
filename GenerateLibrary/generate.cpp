#include "generate.h"

//void stepMatrix(list<RightPayload>& result, RightPayload elem, int new_n, int d, set<map<int, vector<long long>>> codewords_map_set) {
void stepMatrix(list<RightPayload>& result, RightPayload elem, int new_n, int d, set<map<int, int>> codewords_map_set, strategy_step st) {
  int k = elem.rows;
  int old_n = elem.cols;
  int dn = new_n - old_n;
  
  /* TODO: ADD COL TYPE GENERATION */
  set<long long> half_set;
  for_each(elem.codewords.begin(), elem.codewords.end(), [&half_set, dn](const long long n){
    half_set.insert(n << dn);
  });
  
  RightPayload half_matrix(half_set, k, new_n, elem.d);
  
  do {
    vector<long long> H = get_H_matrix(half_matrix);
    list<vector<long long>> leaders = get_potential_leaders(H, half_matrix, st, d);

    for (list<vector<long long>>::iterator it = leaders.begin(); it != leaders.end(); ++it) {
      RightPayload new_matrix = add_leaders_to_system_payload(half_matrix, *it);
      if (!update_print_set(codewords_map_set, new_matrix, d)) {
        continue;
      } else {
	std::cout << "\n";
	new_matrix.print();
        result.push_back(new_matrix);
      }
    }
    return;
  } while (true);
}

int generate_new_n(int k, int n, int k_step, int d) {
  for (int i = 0; i < k_step; i++) {
    n = get_next_n(k, n, d);
    k++;
  }
  return n;
}

list<RightPayload> step_matrices(list<RightPayload> matrices, strategy_step st, int d) {
  list<RightPayload> result;
  int new_pre_n = generate_new_n(matrices.back().rows, matrices.back().cols + matrices.back().rows, st.k_step, d) - matrices.back().rows;
  while (result.empty()) {
    //set<map<int, vector<long long>>> codewords_map_set;
    set<map<int, int>> codewords_map_set;
    int i = 1;
    for (RightPayload elem : matrices) {
      stepMatrix(result, elem, new_pre_n, d, codewords_map_set, st);
      std::cout << "Step " << i << " out of " << matrices.size() << " done\n";
      i++;
    }
    if (result.empty()) {
      std::cout << "Matrices with specified n not found";
      throw -1;
    }
    new_pre_n++;
  }
  return result;
}
