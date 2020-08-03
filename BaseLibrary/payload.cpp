#include "base.h"

RightPayload::RightPayload(set<long long>& codewords, int rows, int cols, int d) {
  this->codewords = codewords;
  this->rows = rows;
  this->cols = cols;
  this->d = d;
}
void RightPayload::add_word(long long word) {
  codewords.insert(word);
  rows++;
}

void RightPayload::print() {
  for_each(this->codewords.begin(), this->codewords.end(), [this](const long long n) {
    long long x = 1LL << (this->cols - 1);
    for (int j = 0; j < this->cols; j++, x >>= 1) {
      if (n & x) std::cout << 1;
      else std::cout << 0;
    }
    std::cout << "\n";
  });
}


vector<long long> get_H_matrix(const RightPayload& p) {
  vector<long long> result(p.cols + p.rows);
  std::copy(p.codewords.begin(), p.codewords.end(), result.begin());
  long long val = 1LL << (p.cols - 1);
  for (int i = 0; i < p.cols; i++) {
    result.push_back(val);
    val >>= 1;
  }
  /*std::cout << "\n";
  for_each(result.begin(), result.end(), [p, &val] (long long &x) {
    val = 1LL << (p.cols - 1);
    for (int j = 0; j < p.cols; j++, val >>= 1) {
      if (x & val) std::cout << 1;
      else std::cout << 0;
    }
    std::cout << "\n";
  });*/
  return result;
}


RightPayload read(ifstream& infile, int rows, int cols, int d) {
  int temp_rows = 0;
  bool buff[MAXBUFSIZE];
  while (!infile.eof() && temp_rows < rows) {
    int temp_cols = 0;
    while (!infile.eof() && temp_cols < cols) {
      infile >> buff[cols*temp_rows + temp_cols++];
    }
    if (temp_cols == 0) continue;

    temp_rows++;
  }
  set<long long> codewords;
  for (int i = 0; i < rows; i++) {
    long long codeword = 0;
    long long power = 1LL << (cols - 1);
    for (int j = 0; j < cols; j++, power >>= 1) {
      if (buff[cols*i + j]) codeword |= power;
    }
    codewords.insert(codeword);
  }
  return RightPayload(codewords, rows, cols, d);
}

list<RightPayload> read_list(const char* filename) {
  ifstream infile;
  infile.open(filename);
  int matrix_num, rows, cols, d;
  infile >> matrix_num >> rows >> cols >> d;
  list<RightPayload> result;
  for (int i = 0; i < matrix_num; i++) {
    RightPayload m = read(infile, rows, cols, d);
    result.push_back(m);
  }
  infile.close();
  return result;
}
