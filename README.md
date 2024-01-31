# Welcome to Linear Algebra Demo

This application allows you to perform various matrix operations.

Available Commands:


| Command      | Syntax                                      | Description                                |
|--------------|---------------------------------------------|--------------------------------------------|
| `stop`       | `stop`                                      | Exit the application.                      |
| `read_mat`   | `read_mat <matrix_name>, <arg1>, <arg2>, ...` | Read a matrix and store its values.       |
| `print_mat`  | `print_mat <matrix_name>`                   | Print the contents of a matrix.            |
| `add_mat`    | `add_mat <matrix1_name>, <matrix2_name>, <result_matrix_name>` | Add two matrices.          |
| `sub_mat`    | `sub_mat <matrix1_name>, <matrix2_name>, <result_matrix_name>` | Subtract one matrix from another.   |
| `mul_mat`    | `mul_mat <matrix1_name>, <matrix2_name>, <result_matrix_name>` | Multiply two matrices.       |
| `mul_scalar` | `mul_scalar <matrix_name>, <scalar>, <result_matrix_name>` | Multiply a matrix by a scalar value. |
| `trans_mat`  | `trans_mat <matrix_name>, <result_matrix_name>` | Transpose a matrix.                    |


## Operation
```
Please enter your instructions:
>> read_mat MAT_A, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
>> print_mat MAT_A
    1.00     0.00     0.00     0.00 
    0.00     1.00     0.00     0.00 
    0.00     0.00     1.00     0.00 
    0.00     0.00     0.00     1.00 
>> 
>> read_mat MAT_B, 4, 7, 2, 3, 0, 1, 0, 0, 2, 3, 4, 7, 0, 0, 0, 1
>> print_mat MAT_B
    4.00     7.00     2.00     3.00 
    0.00     1.00     0.00     0.00 
    2.00     3.00     4.00     7.00 
    0.00     0.00     0.00     1.00 
>> 
>> read_mat MAT_C, 0.3333, -1.8333, -0.1667, 0.1667, 0, 1, 0, 0, -0.1667, 0.1667, 0.3333, -1.8333, 0, 0, 0, 1
>> print_mat MAT_C
    0.33    -1.83    -0.17     0.17 
    0.00     1.00     0.00     0.00 
   -0.17     0.17     0.33    -1.83 
    0.00     0.00     0.00     1.00 
>> add_mat MAT_A, MAT_B, MAT_D
>> print_mat MAT_D
    5.00     7.00     2.00     3.00 
    0.00     2.00     0.00     0.00 
    2.00     3.00     5.00     7.00 
    0.00     0.00     0.00     2.00 
>> 
>> sub_mat MAT_B, MAT_A, MAT_D
>> print_mat MAT_D
    3.00     7.00     2.00     3.00 
    0.00     0.00     0.00     0.00 
    2.00     3.00     3.00     7.00 
    0.00     0.00     0.00     0.00 
>> stop
```
