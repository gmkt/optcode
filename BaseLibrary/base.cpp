#include "base.h"
#include <iostream>

int get_min_coeff(int idx, long long word, int cols) {
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

int dist(long long a, long long b) {
  long long c = a ^ b;
  int d = 0;
  while (c > 0) {
    if (c % 2) d++;
    c >>= 1;
  }
  return d;
}

int add_new_leader(list<set<long long>>& dims, RightPayload payload, long long leader, int total_cols) {
  //TODO: go through dims and add leader to dim only if all possible combinations 
  //of vectors from dim with leader exist within said dim
  set<long long> new_leader_set;
  new_leader_set.insert(leader);
  dims.push_back(new_leader_set);
  return 1;
}

list<set<long long>> get_potential_leaders(vector<long long> H, RightPayload payload, int d) {
  queue<synd_entry*> q;
  set<long long> was;
  int r = payload.cols;
  int actual_k = payload.rows;
  int n = H.size();
  long long nm = 1LL << (n - 1);
  for (int i = 0; i < n; i++, nm >>= 1) {
    q.push(new synd_entry(H[i], nm, 1, n-1-i));
    was.insert(H[i]);
  }
  int w = 1;
  long long ns = n;
  long long N = (1LL << r) - 1;
  list<long long> result;
  list<set<long long>> dims;
  int max = 0;
  while (ns < N) {
    w++;
    //std::cout << w << endl;
    int q_s = q.size();
    for (int rrr = 0; rrr < q_s; rrr++) {
      synd_entry* el = q.front();
      for (int j = el->l + 1; j < n; j++) {
        long long nr = el->s ^ H[n - 1 - j];
        if (nr != 0) {
          if (was.find(nr) == was.end()) {
            if (!(el->c & (1LL << j))) {
              long long c = el->c | (1LL << j);
              if (w >= d) {
                //std::cout << c << endl;
                  //int v = add_new_leader(dims, payload, c, n);
                  //if (v > max) {
                    //max = v;
                  //result.push_back(c);
              }
              q.push(new synd_entry(nr, c, w, j));
            }
            ns++;
            was.insert(nr);
          }
        }
      }
      delete el;
      q.pop();
    }
  }
  while (!q.empty()) {
    if (w >= d) {
      add_new_leader(dims, payload, q.front()->s, n);
    }
    delete q.front();
    q.pop();
  }

  list<set<long long>> res;

  list<set<long long>>::iterator it = dims.begin();
  while (it != dims.end()) {
    if (it->size() >= max) {
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

RightPayload add_leaders_to_system_payload(RightPayload payload, set<long long> leaders) {
  vector<long long> vec;
  vec.reserve(payload.codewords.size() + leaders.size());
  for_each(payload.codewords.begin(), payload.codewords.end(), [&vec](const long long &x) {
    vec.push_back(x);
  });
  for (set<long long>::iterator it = leaders.begin(); it != leaders.end(); ++it) {
    vec.push_back(*it);
  }
  for (int i = payload.codewords.size(); i < vec.size(); i++) {
    int actual_coeff = (payload.cols - 1 - i + payload.codewords.size());
    int x = get_min_coeff(actual_coeff, vec[i], payload.cols);
    bool eq = (x == actual_coeff);
    if (!eq) {
      vec[i] = replace_bits(x, actual_coeff, vec[i]);
    }
    for (int j = 0; j < vec.size(); j++) {
      if (j != i) {
        if (!eq) {
          vec[j] = replace_bits(x, actual_coeff, vec[j]);
        }
        if (vec[j] & (1LL << actual_coeff)) {
          vec[j] ^= vec[i];
        }
      }
    }
  }
  long long power = 1LL << payload.cols - leaders.size();
  set<long long> new_codewords;
  for (int i = 0; i < vec.size(); i++) {
    vec[i] %= power;
    new_codewords.insert(vec[i]);
  }

  return RightPayload(new_codewords, vec.size(), payload.cols - leaders.size(), payload.d);
}

int count_ones(long long v, int cols) {
  int r = 0;
  for (long long power = 1; power < (1LL << cols); power <<= 1) {
    if (power & v) r++;
  }
  return r;
}

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

//bool update_print_set(set<map<int, vector<long long>>>& print_set, RightPayload p) {
bool update_print_set(set<map<int, int>>& print_set, RightPayload p, int d) {
  //map<int, vector<long long>> mp;
  map<int, int> mp;
  for (set<long long>::iterator it = p.codewords.begin(); it != p.codewords.end(); ++it) {
    int c = count_ones(*it, p.cols);
    //map<int, vector<long long>>::iterator entry = mp.find(c);
    if (c < d - 1) return false;
    map<int, int>::iterator entry = mp.find(c);
    if (entry == mp.end()) {
      mp[c] = 1;
    } else {
      entry->second++;
    }
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
  if (print_set.find(mp) == print_set.end()) {
    print_set.insert(mp);
    return true;
  } else {
    return false;
  }
}
