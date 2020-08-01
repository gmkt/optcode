#include "generate.h"

int get_next_column_id(int prev_i, vector<vector<bool>>& my_vec, int col_size, int max_prev) {
  bool is_max = true;
  while (is_max == true && prev_i >= 0) {
    for (int i = 0; i < col_size && is_max; i++) {
      if (!my_vec[i][prev_i]) is_max = false;
    }
    if (is_max) prev_i--;
  }
  if (prev_i >= 0) {
    int i = col_size - 1;
    while (my_vec[i][prev_i] && i >= 0) {
      my_vec[i][prev_i] = false;
      i--;
    }
    my_vec[i][prev_i] = true;
    for (int j = prev_i + 1; j <= max_prev; j++) {
      for (int l = 0; l < col_size; l++) {
        my_vec[l][j] = my_vec[l][prev_i];
      }
    }
    return max_prev;
  }
  return prev_i;
}

void step_matrix(list<RightPayload>& result, RightPayload elem, int new_n, int d, set<set<long long>>& codewords_set_set, set<map<int, int>>& weight_map_set, strategy_step st) {
  int k = elem.rows;
  int old_n = elem.cols;
  int dn = new_n - old_n;
  
  set<long long> half_set;
  vector<vector<bool>> my_vec;
  my_vec.reserve(elem.rows);
  for_each(elem.codewords.begin(), elem.codewords.end(), [&half_set, &my_vec, dn](const long long n){
    half_set.insert(n << dn);
    if (dn != 1) {
      vector<bool> local_vec;
      local_vec.insert(local_vec.begin(), dn - 1, false);
      my_vec.push_back(local_vec);
    }
  });
  
  RightPayload half_matrix(half_set, k, new_n, elem.d);
  
  bool keep_going;
  int prev_i = dn - 2;
  do {
    keep_going = true;
    vector<long long> H = get_H_matrix(half_matrix);
    list<vector<long long>> leaders = get_potential_leaders(H, half_matrix, st, d);

    for (list<vector<long long>>::iterator it = leaders.begin(); it != leaders.end(); ++it) {
      RightPayload new_matrix = add_leaders_to_system_payload(half_matrix, *it);
      if (!check_matrix(codewords_set_set, weight_map_set, new_matrix, d, true)) {
        continue;
      } else {
	std::cout << "\n";
	new_matrix.print();
        result.push_back(new_matrix);
      }
    }
    if (dn > 1) {
      prev_i = get_next_column_id(prev_i, my_vec, k, dn - 2);
      if (prev_i == -1) return;
      half_matrix.codewords.clear();
      int i = 0;
      for_each(elem.codewords.begin(), elem.codewords.end(), [&half_matrix, &i, &my_vec, dn](const long long n){
        long long w = 0;
        long long step = 1;
        for (int j = dn - 2; j >= 0; j--, step <<= 1) {
          if (my_vec[i][j]) w |= step;
        }
        half_matrix.codewords.insert((n << dn) + w);
        i++;
      });
    } else return;
  } while (prev_i >= 0);
  return;
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
    set<set<long long>> codewords_set_set;
    set<map<int, int>> weight_map_set;
    int i = 1;
    for (RightPayload elem : matrices) {
      step_matrix(result, elem, new_pre_n, d, codewords_set_set, weight_map_set, st);
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


