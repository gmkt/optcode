executable usage:
ctd _distance_
generates codes with maximum possible size and minimum length using hypothesis that these codes can be generated recursively
ctd_reusable _input_file_path_
does the same as ctd but uses input_file_path as recursion base with following format:
_matrices_num_ _rows_num_ _cols_num_ _distance_
_Matrix_description_1_
_Matrix_description_2_
...
_Matrix_description_matrices_num_
Matrix description is basically matrix itself written down with spaces inbetween 1s or 0s.
There's example input.txt
