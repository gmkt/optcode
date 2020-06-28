#include "bound.h"

const int MAX_NK = 64;

long long c[MAX_NK][MAX_NK];
int hem[MAX_NK][MAX_NK][MAX_NK];
int vg[MAX_NK][MAX_NK][MAX_NK];
int gr[MAX_NK][MAX_NK];
int known_bounds[MAX_NK][MAX_NK];

void init_bounds() {
  known_bounds[4][4] = 8; // bound
  known_bounds[5][4] = 10;
  known_bounds[6][4] = 11;
  known_bounds[7][4] = 12;
  known_bounds[8][4] = 13;
  known_bounds[9][4] = 14;
  known_bounds[10][4] = 15;
  known_bounds[11][4] = 16; // bound
  known_bounds[12][4] = 18;
  known_bounds[13][4] = 19;
  known_bounds[14][4] = 20;
  known_bounds[15][4] = 21;
  known_bounds[16][4] = 22;
  known_bounds[17][4] = 23;
  known_bounds[18][4] = 24;
  known_bounds[19][4] = 25;
  known_bounds[20][4] = 26;
  known_bounds[21][4] = 27;
  known_bounds[22][4] = 28;
  known_bounds[23][4] = 29;
  known_bounds[24][4] = 30;
  known_bounds[25][4] = 31;
  known_bounds[26][4] = 32; // bound
  known_bounds[27][4] = 34;
  known_bounds[28][4] = 35;
  known_bounds[29][4] = 36;
  known_bounds[30][4] = 37;
  known_bounds[31][4] = 38;
  known_bounds[32][4] = 39;
  known_bounds[33][4] = 40;
  known_bounds[3][5] = 10;
  known_bounds[4][5] = 11; // bound
  known_bounds[5][5] = 13;
  known_bounds[6][5] = 14;
  known_bounds[7][5] = 15;
  known_bounds[8][5] = 16;
  known_bounds[9][5] = 17; // bound
  known_bounds[10][5] = 19;
  known_bounds[11][5] = 20;
  known_bounds[12][5] = 21;
  known_bounds[13][5] = 22;
  known_bounds[14][5] = 23; // bound
  known_bounds[15][5] = 25;
  known_bounds[16][5] = 26;
  known_bounds[17][5] = 27;
  known_bounds[18][5] = 28;
  known_bounds[19][5] = 29;
  known_bounds[20][5] = 30;
  known_bounds[21][5] = 31;
  known_bounds[22][5] = 32;
  known_bounds[23][5] = 33; // bound
  known_bounds[24][5] = 35;
  known_bounds[25][5] = 36;
  known_bounds[26][5] = 37;
  known_bounds[27][5] = 38;
  known_bounds[28][5] = 39;
  known_bounds[29][5] = 40;
  known_bounds[3][6] = 11;
  known_bounds[4][6] = 12; // bound
  known_bounds[5][6] = 14;
  known_bounds[6][6] = 15;
  known_bounds[7][6] = 16;
  known_bounds[8][6] = 17;
  known_bounds[9][6] = 18; // bound
  known_bounds[10][6] = 20;
  known_bounds[11][6] = 21;
  known_bounds[12][6] = 22;
  known_bounds[13][6] = 23;
  known_bounds[14][6] = 24; // bound
  known_bounds[15][6] = 26;
  known_bounds[16][6] = 27;
  known_bounds[17][6] = 28;
  known_bounds[18][6] = 29;
  known_bounds[19][6] = 30;
  known_bounds[20][6] = 31;
  known_bounds[21][6] = 32;
  known_bounds[22][6] = 33;
  known_bounds[23][6] = 34; // bound
  known_bounds[24][6] = 36;
  known_bounds[25][6] = 37;
  known_bounds[26][6] = 38;
  known_bounds[27][6] = 39;
  known_bounds[28][6] = 40;
  known_bounds[3][7] = 13;
  known_bounds[4][7] = 14;
  known_bounds[5][7] = 15; // bound
  known_bounds[6][7] = 17;
  known_bounds[7][7] = 18;
  known_bounds[8][7] = 19;
  known_bounds[9][7] = 20;
  known_bounds[10][7] = 21;
  known_bounds[11][7] = 22;
  known_bounds[12][7] = 23; // bound (HUGE)
  known_bounds[13][7] = 26;
  known_bounds[14][7] = 27; // bound
  known_bounds[15][7] = 29;
  known_bounds[16][7] = 30;
  known_bounds[17][7] = 31;
  known_bounds[18][7] = 32; // ??
  known_bounds[19][7] = 33;
  known_bounds[20][7] = 34;
  known_bounds[21][7] = 35;
  known_bounds[22][7] = 36;
  known_bounds[23][7] = 37;
  known_bounds[24][7] = 38;
  known_bounds[25][7] = 39;
  known_bounds[26][7] = 40;
  known_bounds[3][8] = 14;
  known_bounds[4][8] = 15;
  known_bounds[5][8] = 16; // bound
  known_bounds[6][8] = 18;
  known_bounds[7][8] = 19;
  known_bounds[8][8] = 20;
  known_bounds[9][8] = 21;
  known_bounds[10][8] = 22;
  known_bounds[11][8] = 23;
  known_bounds[12][8] = 24; // bound (HUGE)
  known_bounds[13][8] = 27;
  known_bounds[14][8] = 28; // bound
  known_bounds[15][8] = 30;
  known_bounds[16][8] = 31;
  known_bounds[17][8] = 32; // ??
  known_bounds[18][8] = 33;
  known_bounds[19][8] = 34;
  known_bounds[20][8] = 35;
  known_bounds[21][8] = 36;
  known_bounds[22][8] = 37;
  known_bounds[23][8] = 38;
  known_bounds[24][8] = 39;
  known_bounds[25][8] = 40;
  known_bounds[3][9] = 17; // bound
  known_bounds[4][9] = 19;
  known_bounds[5][9] = 20; // bound
  known_bounds[6][9] = 22;
  known_bounds[7][9] = 23; // bound
  known_bounds[8][9] = 25;
  known_bounds[9][9] = 26;
  known_bounds[10][9] = 27; // bound
  known_bounds[11][9] = 29;
  known_bounds[12][9] = 30;
  known_bounds[13][9] = 31;
  known_bounds[14][9] = 32; // ??
  known_bounds[15][9] = 33;
  known_bounds[16][9] = 34; // bound
  known_bounds[17][9] = 36;
  known_bounds[18][9] = 37;
  known_bounds[19][9] = 38;
  known_bounds[20][9] = 39;
  known_bounds[21][9] = 40;
  known_bounds[3][10] = 18; // bound
  known_bounds[4][10] = 20;
  known_bounds[5][10] = 21; // bound
  known_bounds[6][10] = 23;
  known_bounds[7][10] = 24; // bound
  known_bounds[8][10] = 26;
  known_bounds[9][10] = 27;
  known_bounds[10][10] = 28; // bound
  known_bounds[11][10] = 30;
  known_bounds[12][10] = 31;
  known_bounds[13][10] = 32;
  known_bounds[14][10] = 33; // ??
  known_bounds[15][10] = 34;
  known_bounds[16][10] = 35; // bound
  known_bounds[17][10] = 37;
  known_bounds[18][10] = 38;
  known_bounds[19][10] = 39;
  known_bounds[20][10] = 40;
  known_bounds[3][11] = 20; // bound
  known_bounds[4][11] = 22;
  known_bounds[5][11] = 23; // bound
  known_bounds[6][11] = 25;
  known_bounds[7][11] = 26; // bound
  known_bounds[8][11] = 28;
  known_bounds[9][11] = 29;
  known_bounds[10][11] = 30;
  known_bounds[11][11] = 31; // bound
  known_bounds[12][11] = 33; // bound
  known_bounds[13][11] = 35;
  known_bounds[14][11] = 36;
  known_bounds[15][11] = 37; // ??
  known_bounds[16][11] = 38;
  known_bounds[17][11] = 39;
  known_bounds[18][11] = 40;
  known_bounds[3][12] = 21; // bound
  known_bounds[4][12] = 23;
  known_bounds[5][12] = 24; // bound
  known_bounds[6][12] = 26;
  known_bounds[7][12] = 27; // bound
  known_bounds[8][12] = 29;
  known_bounds[9][12] = 30;
  known_bounds[10][12] = 31;
  known_bounds[11][12] = 32; // bound
  known_bounds[12][12] = 34; // bound
  known_bounds[13][12] = 36;
  known_bounds[14][12] = 37;
  known_bounds[15][12] = 38; // ??
  known_bounds[16][12] = 39;
  known_bounds[17][12] = 40;
  known_bounds[3][13] = 24; // bound
  known_bounds[4][13] = 26;
  known_bounds[5][13] = 27; // bound
  known_bounds[6][13] = 29; // bound
  known_bounds[7][13] = 31;
  known_bounds[8][13] = 32; // bound
  known_bounds[9][13] = 34;
  known_bounds[10][13] = 35; // ??
  known_bounds[11][13] = 36;
  known_bounds[12][13] = 37; // bound
  known_bounds[13][13] = 39;
  known_bounds[14][13] = 40;
  known_bounds[3][14] = 25; // bound
  known_bounds[4][14] = 27;
  known_bounds[5][14] = 28; // bound
  known_bounds[6][14] = 30; // bound
  known_bounds[7][14] = 32;
  known_bounds[8][14] = 33; // bound
  known_bounds[9][14] = 35;
  known_bounds[10][14] = 36; // ??
  known_bounds[11][14] = 37;
  known_bounds[12][14] = 38; // bound
  known_bounds[13][14] = 40;
  known_bounds[3][15] = 27; // bound
  known_bounds[4][15] = 29;
  known_bounds[5][15] = 30;
  known_bounds[6][15] = 31; // bound (HUGE)
  known_bounds[7][15] = 34;
  known_bounds[8][15] = 35; // bound
  known_bounds[9][15] = 37; // bound
  known_bounds[10][15] = 39;
  known_bounds[11][15] = 40;
  known_bounds[3][16] = 28; // bound
  known_bounds[4][16] = 30;
  known_bounds[5][16] = 31;
  known_bounds[6][16] = 32; // bound (HUGE)
  known_bounds[7][16] = 35;
  known_bounds[8][16] = 36; // bound
  known_bounds[9][16] = 38; // bound
  known_bounds[10][16] = 40;
  known_bounds[3][17] = 31; // bound (HUGE)
  known_bounds[4][17] = 34; // bound
  known_bounds[5][17] = 36;
  known_bounds[6][17] = 37; // bound
  known_bounds[7][17] = 39;
  known_bounds[3][18] = 32; // bound (HUGE)
  known_bounds[4][18] = 35; // bound
  known_bounds[5][18] = 37;
  known_bounds[6][18] = 38; // bound
  known_bounds[7][18] = 40;
  known_bounds[3][19] = 34; // bound (HUGE)
  known_bounds[4][19] = 37; // bound
  known_bounds[5][19] = 39;
  known_bounds[3][20] = 35; // bound (HUGE)
  known_bounds[4][20] = 38; // bound
  known_bounds[5][20] = 40;
  known_bounds[3][21] = 38;
  known_bounds[3][22] = 39;
}

long long get_c(int n, int k) {
  // check for incorrect n and k
  if (k > n || k < 0 || n < 0) return -1; //TODO: throw
  // check whether c[n][k] is already calculated
  if (c[n][k] != 0) return c[n][k];
  // if selecting from 0 or n, c equals 1
  if (k == n || k == 0) c[n][k] = 1;
  // otherwise try to calculate it from opposite one
  else if (c[n][n - k] != 0) c[n][k] = c[n][n - k];
  // otherwise recursively calculate it
  else c[n][k] = get_c(n - 1, k) + get_c(n - 1, k - 1);
  return c[n][k];
}

// exists for convenience
inline long long pow2(int n) {
  return 1LL << n;
}

int hemming(int prev_k, int prev_n, int d) {
  // check for incorrect prev_k and prev_n and d
  if (prev_k <= 0 || prev_n <= 0 || d <= 0 || prev_k > prev_n) return -1; //TODO: throw
  // check whether hem[prev_k][prev_n][d] is already calculated
  if (hem[prev_k][prev_n][d] != 0) return hem[prev_k][prev_n][d];
  // calculate t - TODO: name properly
  int t = (d - 1) / 2;
  // new_k is incremented previous
  int new_k = prev_k + 1;
  // try to fit in the same n
  int new_n = prev_n;
  long long min = pow2(new_n - new_k);
  long long sum = 0;
  for (int i = 0; i <= t; i++) {
    sum += get_c(new_n, i);
  }
  // search for power of 2 which allows to fit sum of following c's
  //bin search?
  while (sum > min) {
    sum = 0;
    new_n++;
    min <<= 1;
    for (int i = 0; i <= t; i++) {
      sum += get_c(new_n, i);
    }
  }
  hem[prev_k][prev_n][d] = new_n;
  return new_n;
}

int varsh_gilb(int prev_k, int prev_n, int d) {
  // check for incorrect prev_k and prev_n and d
  if (prev_k <= 0 || prev_n <= 0 || d <= 0 || prev_k > prev_n) return -1; //TODO: throw
  // check whether vg[prev_k][prev_n][d] is already calculated
  if (vg[prev_k][prev_n][d] != 0) return vg[prev_k][prev_n][d];
  int new_k = prev_k + 1;
  int new_n = prev_n;
  long long min = pow2(new_n - new_k);
  long long sum = 0;
  for (int i = 0; i <= d - 2; i++) {
    sum += get_c(new_n - 1, i);
  }
  // search for power of 2 which allows to fit sum of following c's
  while (sum >= min) {
    sum = 0;
    new_n++;
    min <<= 1;
    for (int i = 0; i <= d - 2; i++) {
      sum += get_c(new_n - 1, i);
    }
  }
  vg[prev_k][prev_n][d] = new_n;
  return new_n;
}

int graismer(int k, int d) {
  // check for incorrect k and d
  if (k <= 0 || d <= 0) return -1; //TODO: throw
  // check whether gr[k][d] is already calculated
  if (gr[k][d] != 0) return gr[k][d];
  int new_n = 0;
  for (int i = 0; i <= k - 1; i++) {
    new_n += (int)ceil((d + 0.0) / pow2(i));
  }
  gr[k][d] = new_n;
  return new_n;
}

// for convenience
int min(int a, int b) {
  return (a < b) ? a : b;
}

// for convenience
int max(int a, int b) {
  return (a > b) ? a : b;
}

int get_next_n(int prev_k, int prev_n, int d) {
  if (known_bounds[prev_k + 1][d]) {
    std::cout << known_bounds[prev_k + 1][d] << " known bound" << std::endl;
    return known_bounds[prev_k + 1][d];
  }
  // hemming bound
  int n1 = hemming(prev_k, prev_n, d);
  // varsh-gilb bound
  int n2 = varsh_gilb(prev_k, prev_n, d);
  // graismer bound
  int n3 = graismer(prev_k + 1, d);
  // next bound
  int next_n = min(max(n1, n3), n2);
  std::cout << next_n << " hamming " << n1 << " and varsh_gilb " << n2 << " and graismer's " << n3 << std::endl;
  return next_n;
}

