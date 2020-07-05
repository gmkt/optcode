executable usage:
ctd <distance>
generates codes with maximum possible size and minimum length using hypothesis that these codes can be generated recursively
ctd_reusable <input_file_path>
does the same as ctd but uses input_file_path as recursion base with following format:
<matrices_num> <rows_num> <cols_num> <distance>
<Matrix_description_1>
<Matrix_description_2>
...
<Matrix_description_<matrices_num>>
Matrix description is basically matrix itself written down with spaces inbetween 1s or 0s.
There's example input.txt
