/*
 * Matrix Manipulation Library
 * ---------------------------
 * This C program file provides a comprehensive suite of functions for matrix operations within a predefined context, 'MatrixContext'.
 * It includes functionalities for initializing, validating, reading, and performing basic arithmetic operations on matrices.
 *
 * Core Functionalities:
 * 1.   initMatrices:               Initializes matrices in the context to default values and sets their profiles.
 * 2.   isValidMatrixName:          Validates matrix names against predefined profiles in the context.
 * 3.   printMatrix:                Prints a matrix based on its name.
 * 4.   getMatrixEnumByName:        Retrieves the enum value of a matrix based on its name.
 * 5.   readMatrix:                 Reads data from an array and assigns it to the specified matrix in the context.
 * 6.   addMatrices:                Performs element-wise addition of two matrices.
 * 7.   subMatrices:                Performs element-wise subtraction between two matrices.
 * 8.   multiplyMatrices:           Conducts matrix multiplication of two matrices.
 * 9.   multiplyScalar:             Scales each element of a matrix by a scalar value.
 * 10.  transposeMatrix:            Transposes a matrix and stores the result in another matrix.
 * 11.  transposeMatrixInPlace:     Transposes a square matrix in-place.
 * 12.  multiplyMatricesInPlace:    Multiplies two matrices, storing the result in one of the input matrices using a temporary matrix.
 * 13.  printAllowedMatrixNames:    Prints a list of all available matrix names in the context.

 * The program relies on 'mymat.h' for the definition of structures and constants such as 'Matrix', 'MatrixContext', and 'MatrixProfile'.
 * It assumes matrices are of fixed size, defined by ROWS and COLS constants, and supports a set number of matrices defined by NUM_MATRICES.
 *
 * Usage:
 * This library is designed to be used in applications requiring basic matrix operations. It is essential to initialize the
 * 'MatrixContext' before using these functions to ensure correct operation and data integrity.
 */


#include <stdbool.h>
#include <stdio.h>  
#include <string.h>
#include "mymat.h"


void initMatrices(MatrixContext *ctx, const MatrixProfile validMatrices[NUM_MATRICES]) {
    /* 
     * Initializes matrices within the given MatrixContext to default values and sets their profiles.
     * Assumes 'ctx' is pre-allocated and relevant size constants are correctly defined.
     */
    int matrix_index;  /* Index for iterating over matrices */
    int row_index;     /* Index for iterating over rows of a matrix */
    int col_index;     /* Index for iterating over columns of a matrix */



    /* Iterate over each matrix to initialize its profile and elements. */
    for (matrix_index = 0; matrix_index < NUM_MATRICES; ++matrix_index) {
        /* Set the matrix profile from the predefined validMatrices array. */
        ctx->profiles[matrix_index] = validMatrices[matrix_index];

        /* Nested loops to initialize each element of the matrix to a default value.
         * Here, we're initializing each element to 0.0.
         */
        for (row_index = 0; row_index < ROWS; ++row_index) {
            for (col_index = 0; col_index < COLS; ++col_index) {
                ctx->matrices[matrix_index].data[row_index][col_index] = 0.0;
            }
        }
    }
}



bool isValidMatrixName(const MatrixContext *ctx, const char *matrixName) {
    /* 
     * Checks for the validity of the given matrix name against the matrix profiles in the context.
     * Assumes 'ctx' contains valid profiles and NUM_MATRICES is accurate.
     */

    int matrix_index;  /* Index for iterating over the matrix profiles */

    /* Loop through each matrix profile in the context */
    for (matrix_index = 0; matrix_index < NUM_MATRICES; matrix_index++) {
        /* Compare the current matrix name in the context with the provided matrixName
         * strcmp returns 0 if the strings are equal */
        if (!strcmp(ctx->profiles[matrix_index].nameString, matrixName)) {
            return true;    /* Return true if a match is found */
        }
    }
    return false;           /* Return false if no match is found after checking all profiles */
}


void printMatrix(const MatrixContext *ctx, const char *matrixName) {
    /* 
     * Function to print the matrix
     * Retrieve the matrix by its name from the context 
     */
    const Matrix mat = ctx->matrices[getMatrixEnumByName(matrixName, ctx)];

    int row, column;                    /* Variables for row and column indices */
    char formatStr[FORMAT_STR_SIZE];    /* Character array to hold the formatted output string */

    /* Dynamically create the format string based on the width and precision for matrix element printing */
    sprintf(formatStr, "%%%d.%df ", MATRIX_PRINT_WIDTH, MATRIX_PRINT_PREC);


    for (row = 0; row < ROWS; ++row) {                  /* Iterate over each row of the matrix */
        for (column = 0; column < COLS; ++column) {     /* Iterate over each column in the current row */
            printf(formatStr, mat.data[row][column]);   /* Print each element in the row using the formatted string */
        } 
        printf("\n");                                   /* Print a new line at the end of each row for better readability */
    }
}



MatrixEnum getMatrixEnumByName(const char *matrixName, const MatrixContext *ctx) {
    /* 
     * Short Description:
     * Finds and returns the enum value of a matrix based on its name.
     * Returns -1 if the matrix name is not found.
     */

    MatrixEnum mat;  /* Variable for iterating over matrix profiles*/

    /* Loop through each matrix profile in the context */
    for (mat = 0; mat < NUM_MATRICES; ++mat) {
        
        /* Compare the current matrix name in the context with the provided matrixName
         * strcmp returns 0 if strings are equal */
        if (!strcmp(ctx->profiles[mat].nameString, matrixName)) {
            return ctx->profiles[mat].name;  /* Return the enum value of the matrix if a match is found */
        }
    }
    /* Return -1 if no match is found after checking all profiles*/
    return -1;
}


void readMatrix(MatrixContext *ctx, const char *matrixName, const double array[ROWS * COLS]) {
    /* 
     * Short Description:
     * Reads data from an array and assigns it to the specified matrix in the context.
     * Relies on 'getMatrixEnumByName' to find the correct matrix by name.
     */

    int index = 0;      /* Index for iterating over the elements in the input array */
    int row, column;    /* Variables for row and column indices in the matrix */

    /* Iterate over each row and column of the matrix */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            /* Assign each element from the array to the corresponding matrix cell */
            /* Uses 'index' to access elements in the linear input array */
            ctx->matrices[getMatrixEnumByName(matrixName, ctx)].data[row][column] = array[index++];
        }
    }
}



void addMatrices(const Matrix *mat1, const Matrix *mat2, Matrix *result) {
    /* 
     * Short Description:
     * Performs element-wise addition of two matrices and stores the result in a third matrix.
     */

    int row;    /* Variable for row index */
    int column; /* Variable for column index */

    /* Iterate over each row and column of the matrices */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            /* Add corresponding elements from mat1 and mat2, and store in result */
            result->data[row][column] = mat1->data[row][column] + mat2->data[row][column];
        }
    }
}


void subMatrices(const Matrix *mat1, const Matrix *mat2, Matrix *result) {
    /* 
     * Short Description:
     * Performs element-wise subtraction of two matrices and stores the result in a third matrix.
     */

    int row;    /* Variable for row index */
    int column; /* Variable for column index */

    /* Iterate over each row and column of the matrices */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            /* Subtract corresponding elements of mat2 from mat1, store in result */
            result->data[row][column] = mat1->data[row][column] - mat2->data[row][column];
        }
    }
}



void multiplyMatrices(const Matrix *mat1, const Matrix *mat2, Matrix *result) {
    /* 
     * Short Description:
     * Performs matrix multiplication of two matrices and stores the result in a third matrix.
     */

    int row, column, inner; /* Variables for row, column, and inner loop indices */

    /* Initialize the result matrix to all zeros */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            result->data[row][column] = 0.0;
        }
    }

    /* Perform matrix multiplication */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            for (inner = 0; inner < COLS; ++inner) {
                /* Accumulate the dot product of the row of mat1 and column of mat2 */
                result->data[row][column] += mat1->data[row][inner] * mat2->data[inner][column];
            }
        }
    }
}


void multiplyScalar(const Matrix *mat, const double scalar, Matrix *result) {
    /* 
     * Short Description:
     * Scales each element of a matrix by a scalar value and stores the result in another matrix.
     */

    int row, column; /* Variables for row and column indices */

    /* Iterate over each row and column of the matrix */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            /* Multiply each element by the scalar and store in the result */
            result->data[row][column] = scalar * mat->data[row][column]; 
        } 
    }
}

void transposeMatrix(const Matrix *original, Matrix *transposed) {
    /* 
     * Short Description:
     * Transposes a matrix, flipping its rows and columns, and stores the result in another matrix.
     */

    int row, column; /* Variables for row and column indices */

    /* Iterate over each row and column of the original matrix */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) { 
            /* Place the element at [row][column] in the original to [column][row] in the transposed */
            transposed->data[column][row] = original->data[row][column];
        }
    }
}


void transposeMatrixInPlace(Matrix *matrix) {
    /* 
     * Short Description:
     * Transposes a square matrix in-place, modifying the original matrix.
     */

    int row, column; /* Variables for row and column indices */
    double temp;     /* Temporary variable for swapping values */

    /* Iterate over the upper triangle of the matrix */
    for (row = 0; row < ROWS; ++row) {
        for (column = row + 1; column < COLS; ++column) {
            /* Swap elements across the diagonal */
            temp = matrix->data[row][column];
            matrix->data[row][column] = matrix->data[column][row];
            matrix->data[column][row] = temp;
        }
    }
}


void multiplyMatricesInPlace(const Matrix *mat1, Matrix *result) {
    /* 
     * Short Description:
     * Multiplies two matrices and stores the result in the 'result' matrix.
     * Uses a temporary matrix to avoid overwriting data in 'result' prematurely.
     */

    Matrix temp; /* Temporary matrix to store intermediate results */
    int row, column, inner; /* Variables for row, column, and inner loop indices */

    /* Initialize the temp matrix to all zeros */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            temp.data[row][column] = 0.0;
        }
    }

    /* Perform matrix multiplication and store in temp */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            for (inner = 0; inner < COLS; ++inner) {
                temp.data[row][column] += result->data[row][inner] * mat1->data[inner][column];
            }
        }
    }

    /* Copy the result from temp back into result */
    for (row = 0; row < ROWS; ++row) {
        for (column = 0; column < COLS; ++column) {
            result->data[row][column] = temp.data[row][column];
        }
    }
}


void printAllowedMatrixNames(const MatrixContext *ctx) {
    /* 
     * Short Description:
     * Prints a list of all available matrix names in the provided MatrixContext.
     */

    int matrix_index; /* Variable for iterating over matrix profiles */

    /* Header message for the list of matrix names */
    printf("Below are the available matrix Names:\n");

    /* Iterate through matrix profiles and print each name */
    for (matrix_index = 0; matrix_index < NUM_MATRICES; matrix_index++)
        printf("%d: %s\t", matrix_index + 1, ctx->profiles[matrix_index].nameString);
    
    /* Print a newline for better formatting */
    printf("\n\n");
}
