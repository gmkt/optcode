#include "systematic.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Please, pass relative path to file with matrix as the second argument."
			<< endl << "Matrix should be in the following format: " << endl << "2 4 2\n1 0 1 0\n0 1 0 1\n";
		return -1;
	}

	RightPayload result = readMatrix(argv[1]);
	cout << "Input matrix in systematic form: " << endl;
        result.print();
        cout << endl;
	set<set<long long>> ignored;
	set<map<int, int>> ignored_map;
	check_matrix(ignored, ignored_map, result, result.d, true);
	/*SplanMatrix splm = turn_to_splan_form(&result);
	cout << "1" << endl;
	cout << *splm.get_matrix() << endl;
	MatrixXb H = get_H_matrix(splm);
	cout << "2" << endl;
	cout << H << endl;
	set<map<int, int>>* new_set = new set<map<int, int>>();
	int d = get_new_d(splm.get_matrix(), splm.get_matrix()->cols(), new_set);
	cout << "D: " << d << endl;
	get_potential_liders(&H, d);
	//cout << "Result matrix: " << endl << turn_to_splan_form(&result).first << endl;
        */
}


RightPayload readMatrix(const char *filename) {
	int cols = 0, rows = 0, temp_rows = 0, d;
	bool buff[MAXBUFSIZE];

	// Read numbers from file into buffer.
	ifstream infile;
	infile.open(filename);
	infile >> rows >> cols >> d;
	while (!infile.eof() && temp_rows < rows) {

		int temp_cols = 0;
		while (!infile.eof() && temp_cols < cols)
			infile >> buff[cols*temp_rows + temp_cols++];

		if (temp_cols == 0)
			continue;

		temp_rows++;
	}

	infile.close();

	temp_rows--;

	// Populate matrix with numbers.
	vector<long long> codewords;
	codewords.reserve(rows);
	for (int i = 0; i < rows; i++) {
          long long cw = 0;
          long long step = 1;
          for (int j = cols - 1; j >= 0; j--, step <<= 1) {
            if (buff[cols*i + j]) cw |= step;
          }
          codewords.push_back(cw);
	}
        int k = 0;
        for_each(codewords.begin(), codewords.end(), [&k, &codewords, cols](long long& cw) {
          int i = get_min_coeff(cols - k - 1, cw);
          replace_columns(cols - 1 - k, i, codewords);
          int cur_k = 0;
          for_each(codewords.begin(), codewords.end(), [&cur_k, cols, cw, k](long long& wrd) {
            if ((k != cur_k) && (wrd & (1LL << (cols - 1 - k)))) wrd ^= cw;
            cur_k++;
          });
          k++;
        });

        set<long long> cws;
        long long pow = 1LL << (cols - rows + 1);
        for_each(codewords.begin(), codewords.end(), [&cws, pow](const long long n) {
          cws.insert(n % pow);
        });

	return RightPayload(cws, rows, cols - rows, d);
};
