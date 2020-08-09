#include "base.h"
#include <iostream>

int get_min_coeff(int idx, long long word) {
  for (; idx > 0; idx--) {
    if (word & (1LL << idx)) {
      return idx;
    }
  }
  return -1; // TODO: throw exception
}

struct synd_entry {
  long long s, c;
  int w, l;
  synd_entry(long long s, long long c, int w, int l) {
    this->s = s;
    this->c = c;
    this->w = w;
    this->l = l;
  }
};

// BUCKET
struct bucket {
  list<long long> leaders;
  long long ml;
  bucket(list<long long> leaders, long long ml) {
    this->ml = ml;
    this->leaders = leaders;
  }
};

int weight(long long c) {
  int d = 0;
  while (c > 0) {
    if (c % 2) d++;
    c >>= 1;
  }
  return d;
}

int dist(long long a, long long b) {
  long long c = a ^ b;
  int d = 0;
  while (c > 0) {
    if (c % 2) d++;
    c >>= 1;
  }
  return d;
}

// BUCKET
long long add_new_leader(long long leader, vector<bucket>& buckets, strategy_step st, long long bucket_num) {
  // Bucket algorithm: divide all leaders into buckets. Within one bucket all leaders are not further than 
  // specified distance(st.dist) from leader of the bucket. Bucket size is limited (st.msize); add after exceedance only 
  // if cannot put into any other bucket - if leaders are distributed unevenly then rearrange(???? takes a lot of time).
  long long bucket_fits = -1;
  for (long long i = 0; i < buckets.size(); i++) {
    if (dist(buckets[i].ml, leader) <= st.dist) {
      if (buckets[i].leaders.size() < bucket_num) {
        buckets[i].leaders.push_back(leader);
        return i;
      } else if (bucket_fits == -1) {
        bucket_fits = i;
      }
    }
  }
  if (buckets.size() < bucket_num) {
    list<long long> leaders;
    buckets.push_back(bucket(leaders, leader));
    return buckets.size() - 1;
  } else {
    if (bucket_fits == -1) {
      std::cout << "UNFITTABLE " << leader << "\n";
      throw -1;
    }
    buckets[bucket_fits].leaders.push_back(leader);
    return bucket_fits;
  }
}

// BUCKET
// Only two leaders are supported
int check_and_update_dim(long long a, long long b, map<long long, long long> all_leaders, list<my_arr>& dims, int d) {
  long long c = a ^ b;
  int w = weight(c);
  if (w >= d) {
    map<long long, long long>::iterator cur_it = all_leaders.find(c);
    if (cur_it != all_leaders.end()) {
      my_arr v(new long long[2], 2);
      v.arr[0] = a;
      v.arr[1] = b;
      dims.push_back(v);
    }
  }
  return w;
}

// BUCKET
// Only two leaders are supported
void sift_through_buckets(map<long long, long long>::iterator it, vector<bucket> buckets, strategy_step st, int d, list<my_arr>& dims, map<long long, long long> all_leaders) {
  for (long long i = 0; i < buckets.size(); i++) {
    if (it->second != i) {
      int w = check_and_update_dim(it->first, buckets[i].ml, all_leaders, dims, d);
      if (w + st.dist >= d) {
        for (list<long long>::iterator cur_it = buckets[i].leaders.begin(); cur_it != buckets[i].leaders.end(); ++cur_it) {
          check_and_update_dim(it->first, *cur_it, all_leaders, dims, d);
        }
      }
    }
  }
}

void for_each_leader(long long iterator, long long end, const my_arr& H, queue<synd_entry*>& q, set<long long>& was, function<void(int w, long long s)> func) {
  int w = 1;
  while (iterator < end) {
    w++;
    //std::cout << w << endl;
    int q_s = q.size();
    for (int rrr = 0; rrr < q_s; rrr++) {
      synd_entry* el = q.front();
      for (int l = el->l + 1; l < H.size; l++) {
        long long s = el->s ^ H.arr[H.size - 1 - l];
        if (s != 0) {
          if (was.find(s) == was.end()) {
            if (!(el->c & (1LL << l))) {
              long long c = el->c | (1LL << l);
              func(w, s);
              q.push(new synd_entry(s, c, w, l));
            }
            iterator++;
            was.insert(s);
          }
        }
      }
      delete el;
      q.pop();
    }
  }
  while (!q.empty()) {
    delete q.front();
    q.pop();
  }
}

list<my_arr> get_potential_leaders(const my_arr& H, int r, strategy_step st, int d) {
  queue<synd_entry*> q;
  set<long long> was;

  // Queue and was init
  int n = H.size;
  long long synd_count = (1LL << r) - 1;
  long long cw = 1LL << (n - 1);
  for (int i = 0; i < n; i++, cw >>= 1) {
    q.push(new synd_entry(H.arr[i], cw, 1, n - 1 - i));
    was.insert(H.arr[i]);
  }

  // Buckets creation
  map<long long, long long> all_leaders;
  list<my_arr> dims;
  long long bucket_num = (synd_count / st.msize);
  vector<bucket> buckets;
  if (st.k_step != 1) {
    buckets.reserve(bucket_num);
  }

  // Check all possible codeword leaders with non-zero unique syndroms
  list<my_arr> res;
  for_each_leader(n, synd_count, H, q, was, [d, st, &res, &all_leaders, &buckets, bucket_num](int w, long long s) {
    if (w >= d) {
      if (st.k_step == 1) {
        my_arr v(new long long[1], 1);
        v.arr[0] = s;
        res.push_back(v);
      } else {
        all_leaders[s] = add_new_leader(s, buckets, st, bucket_num);
      }
    }
  });

  std::cout << all_leaders.size() << "\n";
  if (st.k_step == 1) return res;
  // TODO: optimize as it is too slow to be used after first iteration
  // Use collected buckets to sift leaders through them
  else {
    for (map<long long, long long>::iterator it = all_leaders.begin(); it != all_leaders.end(); ++it) { 
      sift_through_buckets(it, buckets, st, d, dims, all_leaders);
    }
  }

  list<my_arr>::iterator it = dims.begin();
  while (it != dims.end()) {
    if (it->size >= 2) {
      res.push_back(*it);
      ++it;
    }
  }
  return res;
}

long long replace_bits(int first, int second, long long v) {
  long long prev_f = v & (1LL << first);
  long long prev_s = v & (1LL << second);
  return (v ^ prev_f ^ prev_s) | ((prev_f != 0) ? 1LL << second : 0) | ((prev_s != 0) ? 1LL << first : 0);
}

RightPayload add_leaders_to_system_payload(const RightPayload& payload, const my_arr& leaders) {
  my_arr vec(new long long[payload.codewords.size() + leaders.size], payload.codewords.size() + leaders.size);
  int j = 0;
  for_each(payload.codewords.begin(), payload.codewords.end(), [&j, &vec](const long long &x) {
    vec.arr[j++] = x;
  });
  for (int i = 0; i < leaders.size; i++) {
    vec.arr[j++] = leaders.arr[i];
  }
  delete[] leaders.arr;
  for (int i = payload.codewords.size(); i < vec.size; i++) {
    int actual_coeff = (payload.cols - 1 - i + payload.codewords.size());
    int x = get_min_coeff(actual_coeff, vec.arr[i]);
    bool eq = (x == actual_coeff);
    if (!eq) {
      vec.arr[i] = replace_bits(x, actual_coeff, vec.arr[i]);
    }
    for (int j = 0; j < vec.size; j++) {
      if (j != i) {
        if (!eq) {
          vec.arr[j] = replace_bits(x, actual_coeff, vec.arr[j]);
        }
        if (vec.arr[j] & (1LL << actual_coeff)) {
          vec.arr[j] ^= vec.arr[i];
        }
      }
    }
  }
  long long power = 1LL << payload.cols - leaders.size;
  set<long long> new_codewords;
  for (int i = 0; i < vec.size; i++) {
    vec.arr[i] %= power;
    new_codewords.insert(vec.arr[i]);
  }
  delete[] vec.arr;

  return RightPayload(new_codewords, vec.size, payload.cols - leaders.size, payload.d);
}

int count_w(long long v, int cols) {
  int r = 0;
  for (long long power = 1; power < (1LL << cols); power <<= 1) {
    if (power & v) r++;
  }
  return r;
}

// MY EQUIV
int replace_and_get_next_coeff(map<int, vector<long long>>::iterator it, int i, map<int, vector<long long>>::iterator m_end, int st, int cols) {
  if (it == m_end) return -1;
  int lg = cols - 1;
  while (lg != st) {
    long long power = 1LL << st;
    while (st < cols && (it->second[i] & power)) {
      power <<= 1;
      st++;
    }
    power = 1LL << lg;
    while (lg > st && !(it->second[i] & power)) {
      lg--;
      power >>= 1;
    }
    if (lg == st || st == cols) return st;
    //it->second[i] = replace_bits(st, lg, it->second[i]);
    map<int, vector<long long>>::iterator it2 = it;
    int j = i;
    while (it2 != m_end) {
      for (; j < it2->second.size(); j++) {
        it2->second[j] = replace_bits(st, lg, it2->second[j]);
      }
      ++it2;
      j = 0;
    }
  }
  return st;
}

bool check_matrix(set<set<long long>>& print_set, set<map<int, int>>& map_set, const RightPayload& p, int d, bool easy_criteria) {
  // easy_criteria = true for comparing by weight map of all combinations of payload codewords
  if (easy_criteria) {
    map<int, int> weight_map;
    my_arr vec(new long long[p.codewords.size()], p.codewords.size());
    set<long long> was;
    queue<synd_entry*> q;
    int k = p.rows;
    long long wrd = 1LL << (k - 1);
    int i = 0;
    for (set<long long>::iterator it = p.codewords.begin(); it != p.codewords.end(); ++it, wrd >>= 1, i++) {
      int c_w = count_w(*it, p.cols) + 1;
      vec.arr[i] = *it;

      q.push(new synd_entry(*it, wrd, 1, k - 1 - i));
      was.insert(*it);

      map<int, int>::iterator entry = weight_map.find(c_w);
      if (entry == weight_map.end()) {
        weight_map[c_w] = 1;
      } else {
        entry->second++;
      }
    }

    // Fill weight_map with number of codewords for each weight from specified linear space
    long long wrd_count = (1LL << k) - 1;
    for_each_leader(k, wrd_count, vec, q, was, [p, &weight_map](int w, long long s) {
      int c_w = count_w(s, p.cols) + w;
      map<int, int>::iterator entry = weight_map.find(c_w);
      if (entry == weight_map.end()) {
        weight_map[c_w] = 1;
      } else {
        entry->second++;
      }
    });

    // Check if it was in map_set before
    if (map_set.find(weight_map) == map_set.end()) {
      map_set.insert(weight_map);
      std::cout << "\nW MAP: \n";
      for (map<int, int>::iterator ittt = weight_map.begin(); ittt != weight_map.end(); ++ittt) {
        std::cout << ittt->first << " " << ittt->second << endl;
      }
      std::cout << endl;
      return true;
    } else {
      return false;
    }
  // easy_criteria = false for comparing by col map of specially sorted payload codewords
  } else {
    // Create map mp with weights as indices and codewords vectors as values
    map<int, vector<long long>> mp;
    for (set<long long>::iterator it = p.codewords.begin(); it != p.codewords.end(); ++it) {
      int c_w = count_w(*it, p.cols) + 1;
      if (c_w < d) return false;
      map<int, vector<long long>>::iterator entry = mp.find(c_w);
      if (entry == mp.end()) {
        vector<long long> cur_vec;
        cur_vec.push_back(*it);
        mp[c_w] = cur_vec;
      } else {
        entry->second.push_back(*it);
      }
    }
    // Collect columns from mp into set
    set<long long> cds;
    for (int i = 0; i < p.cols; i++) {
      long long power = 1LL;
      long long el = 0;
      for (map<int, vector<long long>>::iterator it = mp.begin(); it != mp.end(); ++it) {
        for (int j = 0; j < it->second.size(); j++) {
          if (it->second[j] & (1LL << i)) {
            el |= power;
          }
          power <<= 1;
        }
      }
      cds.insert(el);
    }

    /*
    map<int, vector<long long>>::iterator it = mp.begin();
    int st = 0;
    int i = 0;
    while (it != mp.end() && st != p.cols) {
      st = replace_and_get_next_coeff(it, i, mp.end(), st, p.cols);
      if (i < it->second.size() - 1) i++;
      else {
        ++it;
        i = 0;
      }
    }
    */

    // Check if it was in print_set before
    if (print_set.find(cds) == print_set.end()) {
      print_set.insert(cds);
      std::cout << "\nW MAP: \n";
      for (map<int, vector<long long>>::iterator ittt = mp.begin(); ittt != mp.end(); ++ittt) {
        std::cout << ittt->first << " " << ittt->second.size() << endl;
      }
      std::cout << endl;
      return true;
    } else {
      return false;
    }
  }
}

