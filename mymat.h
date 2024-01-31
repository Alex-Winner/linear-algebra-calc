/*
 * Matrix Manipulation Library Header
 * -----------------------------------
 * This C header file complements the "mymat.c" implementation by providing the necessary
 * structure definitions, constants, and function declarations for matrix operations within
 * a predefined context, 'MatrixContext'.
 *
 * Core Structures and Constants:
 * - Matrix:        A structure representing a 2D matrix with double-precision elements.
 * - MatrixEnum:    An enumeration representing different matrix names.
 * - MatrixProfile: A structure associating matrix names with their string representations.
 * - MatrixContext: A structure to store multiple matrices and their profiles.
 *
 * Core Functions:
 * - initMatrices:              Initializes matrices in the context to default values and sets their profiles.
 * - isValidMatrixName:         Validates matrix names against predefined profiles in the context.
 * - printMatrix:               Prints a matrix based on its name.
 * - getMatrixEnumByName:       Retrieves the enum value of a matrix based on its name.
 * - readMatrix:                Reads data from an array and assigns it to the specified matrix in the context.
 * - addMatrices:               Performs element-wise addition of two matrices.
 * - subMatrices:               Performs element-wise subtraction between two matrices.
 * - multiplyMatrices:          Conducts matrix multiplication of two matrices.
 * - multiplyScalar:            Scales each element of a matrix by a scalar value.
 * - transposeMatrix:           Transposes a matrix and stores the result in another matrix.
 * - transposeMatrixInPlace:    Transposes a square matrix in-place.
 * - multiplyMatricesInPlace:   Multiplies two matrices, storing the result in one of the input matrices using a temporary matrix.
 * - printAllowedMatrixNames:   Prints a list of all available matrix names in the context.
 *
 * Usage:
 * To utilize the functionalities provided by this library, include this header file in your C program
 * and ensure that the "mymat.c" source file is compiled and linked with your application. Initialize
 * the 'MatrixContext' structure before using these functions to ensure correct operation and data integrity.
 *
 * Note:
 * This library assumes matrices are of fixed size, defined by ROWS and COLS constants, and supports a
 * set number of matrices defined by NUM_MATRICES. Ensure that the constants in "mymat.c" and "mymat.h"
 * match the intended matrix dimensions and context size.
 */

/* Constants for controlling the dimentions of the matrix */
#define ROWS 4
#define COLS 4

/* Constants for controlling the format of the printed matrix elements */
/* Total width of each printed number */
#define MATRIX_PRINT_WIDTH 8
/* Number of decimal places */
#define MATRIX_PRINT_PREC  2   
/* format size string for printing matrix elements */
#define FORMAT_STR_SIZE MATRIX_PRINT_WIDTH + MATRIX_PRINT_PREC

/* Define a structure to represent a matrix */
typedef struct {
    /*  2D array to store the elements of the matrix.
        Each element is of type double, which allows storing real numbers with double precision.
        The size of the array is determined by the ROWS and COLS constants,
        representing the dimensions of the matrix */
    double data[ROWS][COLS];
} Matrix;

/* Define an enumeration to represent different matrix names */
typedef enum {
    MAT_A,
    MAT_B,
    MAT_C,
    MAT_D,
    MAT_E,
    MAT_F,
    NUM_MATRICES /* Total number of matrices in the enumeration */
} MatrixEnum;

/* Define a structure to associate matrix names with their string representations */
typedef struct {
    MatrixEnum name;
    const char *nameString;
} MatrixProfile;

/* Define a structure to store multiple matrices and their profiles */
typedef struct {
    Matrix matrices[NUM_MATRICES];
    MatrixProfile profiles[NUM_MATRICES];
} MatrixContext;


/*
 * Function: initMatrices
 * Purpose: Initialize the matrices in a given MatrixContext.
 * Detailed Description:
 *   This function is designed to initialize each matrix within a provided MatrixContext structure.
 *   It sets the profiles for each matrix from a predefined set of valid matrices and initializes
 *   all matrix elements to a default value (zero). The function assumes that the MatrixContext
 *   structure (pointed by 'ctx') is pre-allocated, and that the constants for the number of matrices 
 *   (NUM_MATRICES), rows (ROWS), and columns (COLS) are predefined and correctly represent the 
 *   dimensions of the matrices.
 *
 * Parameters:
 *   ctx - Pointer to the MatrixContext structure to be initialized.
 *
 * Returns: None (void function).
 */
void initMatrices(MatrixContext *ctx, const MatrixProfile validMatrices[NUM_MATRICES]);


/*
 * Function: printMatrix
 * Purpose: Prints the elements of a specified matrix in a formatted way.
 * Detailed Description:
 *   This function is designed to print the elements of a matrix whose name is provided. It first
 *   retrieves the matrix from the MatrixContext based on the given name. Then, it iterates over
 *   each element of the matrix, printing them with a specified width and precision.
 * 
 *   The function assumes that the matrix name provided exists in the context and that the constants 
 *   ROWS and COLS accurately represent the dimensions of the matrix. It also relies on a helper 
 *   function 'getMatrixEnumByName' to map the matrix name to its corresponding enum value.
 * 
 * Parameters:
 *   ctx - Pointer to the MatrixContext structure containing the matrix.
 *   matrixName - Pointer to a character array (string) representing the name of the matrix to be printed.
 *
 * Returns: None (void function).
 */
void printMatrix(const MatrixContext *ctx, const char *matrixName);


/*
 * Function: readMatrix
 * Purpose: Reads data from an array and fills a specified matrix within the MatrixContext.
 * Detailed Description:
 *   This function takes a linear array of double values and assigns these values to the 
 *   corresponding matrix in the MatrixContext identified by the matrixName. The function assumes
 *   the array contains enough elements (ROWS * COLS) to fill the entire matrix and that the
 *   matrix name provided exists in the context.
 *
 *   It uses 'getMatrixEnumByName' to find the index of the matrix in the MatrixContext and then
 *   iterates over each element of the array, assigning it to the appropriate position in the
 *   matrix.
 *
 * Parameters:
 *   ctx - Pointer to the MatrixContext structure containing the matrix to be filled.
 *   matrixName - Pointer to a character array (string) representing the name of the matrix.
 *   array - Pointer to the array of double values to be read into the matrix.
 *
 * Returns: None (void function).
 */
void readMatrix(MatrixContext *ctx, const char *matrixName, const double array[ROWS * COLS]);


/*
 * Function: addMatrices
 * Purpose: Adds two matrices and stores the result in a third matrix.
 * Detailed Description:
 *   This function performs element-wise addition of two matrices (mat1 and mat2) and stores 
 *   the result in the 'result' matrix. It assumes that all matrices are of the same size, defined
 *   by the constants ROWS and COLS.
 *
 *   The function iterates over each element of the matrices, summing the corresponding elements
 *   from mat1 and mat2, and storing the result in the same position in the 'result' matrix.
 *
 * Parameters:
 *   mat1 - Pointer to the first Matrix structure for addition.
 *   mat2 - Pointer to the second Matrix structure for addition.
 *   result - Pointer to the Matrix structure where the result will be stored.
 *
 * Returns: None (void function).
 */
void addMatrices(const Matrix *mat1, const Matrix *mat2, Matrix *result);


/*
 * Function: subMatrices
 * Purpose: Subtracts one matrix from another and stores the result in a third matrix.
 * Detailed Description:
 *   This function performs element-wise subtraction between two matrices (mat1 and mat2)
 *   and stores the result in the 'result' matrix. It iterates over each element of the matrices,
 *   subtracting the corresponding elements of mat2 from mat1, and storing the outcome in the 
 *   respective position in the 'result' matrix.
 *
 *   The function assumes that all involved matrices have the same dimensions, defined by 
 *   the constants ROWS and COLS.
 *
 * Parameters:
 *   mat1 - Pointer to the first Matrix structure for subtraction (minuend).
 *   mat2 - Pointer to the second Matrix structure for subtraction (subtrahend).
 *   result - Pointer to the Matrix structure where the result will be stored (difference).
 *
 * Returns: None (void function).
 */
void subMatrices(const Matrix *mat1, const Matrix *mat2, Matrix *result);


/*
 * Function: multiplyMatrices
 * Purpose: Multiplies two matrices and stores the result in a third matrix.
 * Detailed Description:
 *   This function performs matrix multiplication of two matrices (mat1 and mat2)
 *   and stores the result in the 'result' matrix. The multiplication is carried out by 
 *   taking the dot product of rows from mat1 with columns from mat2. The function first
 *   initializes the 'result' matrix to all zeros and then computes the product.
 *
 *   It assumes that the matrices are square (or at least conformable for multiplication),
 *   with dimensions defined by the constants ROWS and COLS.
 *
 * Parameters:
 *   mat1 - Pointer to the first Matrix structure for multiplication.
 *   mat2 - Pointer to the second Matrix structure for multiplication.
 *   result - Pointer to the Matrix structure where the result will be stored.
 *
 * Returns: None (void function).
 */
void multiplyMatrices(const Matrix *mat1, const Matrix *mat2, Matrix *result);


/*
 * Function: multiplyMatricesInPlace
 * Purpose: Multiplies two matrices and stores the result in one of the input matrices.
 * Detailed Description:
 *   This function multiplies a given matrix (mat1) with another matrix (result) and stores 
 *   the result back in the 'result' matrix. To avoid modifying the 'result' matrix before 
 *   the multiplication is complete, a temporary matrix (temp) is used. After computing the 
 *   multiplication, the function copies the results from the temp matrix back into the 'result' 
 *   matrix.
 *
 *   The function assumes that both matrices are of the same size and square, with dimensions 
 *   defined by the constants ROWS and COLS.
 *
 * Parameters:
 *   mat1 - Pointer to the first Matrix structure used in multiplication.
 *   result - Pointer to the second Matrix structure; the result will be stored here.
 *
 * Returns: None (void function).
 */
void multiplyMatricesInPlace(const Matrix *mat1, Matrix *result);


/*
 * Function: multiplyScalar
 * Purpose: Multiplies a matrix by a scalar value and stores the result in another matrix.
 * Detailed Description:
 *   This function scales each element of a given matrix (mat) by a specified scalar value
 *   and stores the resulting scaled matrix in the 'result' matrix. It iterates over each
 *   element of the input matrix, multiplies it by the scalar, and assigns the result to the
 *   corresponding position in the 'result' matrix.
 *
 *   The function assumes that the dimensions of the input and result matrices are the same, 
 *   defined by the constants ROWS and COLS.
 *
 * Parameters:
 *   mat - Pointer to the Matrix structure to be scaled.
 *   scalar - The scalar value by which each element of the matrix is multiplied.
 *   result - Pointer to the Matrix structure where the result will be stored.
 *
 * Returns: None (void function).
 */
void multiplyScalar(const Matrix *mat, const double scalar, Matrix *result);


/*
 * Function: transposeMatrix
 * Purpose: Transposes a matrix and stores the result in another matrix.
 * Detailed Description:
 *   This function transposes a given matrix (original) and stores the transposed matrix
 *   in 'transposed'. Transposing a matrix involves swapping rows with columns; the element
 *   at [row][column] in the original matrix is placed at [column][row] in the transposed matrix.
 *
 *   The function assumes that the dimensions of the input and result matrices are compatible
 *   for transposition, defined by the constants ROWS and COLS.
 *
 * Parameters:
 *   original - Pointer to the Matrix structure to be transposed.
 *   transposed - Pointer to the Matrix structure where the transposed matrix will be stored.
 *
 * Returns: None (void function).
 */
void transposeMatrix(const Matrix *original, Matrix *transposed);


/*
 * Function: transposeMatrixInPlace
 * Purpose: Transposes a matrix in-place.
 * Detailed Description:
 *   This function transposes the given matrix (matrix) in-place, meaning that it 
 *   modifies the matrix directly rather than creating a new transposed matrix. The function 
 *   swaps elements across the diagonal of the matrix, effectively flipping its rows and columns.
 *
 *   It is important to note that this operation is only valid for square matrices (where the 
 *   number of rows equals the number of columns). The function assumes that the matrix is square,
 *   with dimensions defined by the constants ROWS and COLS.
 *
 * Parameters:
 *   matrix - Pointer to the Matrix structure that will be transposed in-place.
 *
 * Returns: None (void function).
 */
void transposeMatrixInPlace(Matrix *matrix);


/*
 * Function: printAllowedMatrixNames
 * Purpose: Prints the names of all matrices available in the MatrixContext.
 * Detailed Description:
 *   This function lists all the matrix names stored in the MatrixContext. It iterates
 *   through the matrix profiles within the context and prints each matrix's name. The function
 *   assumes that the MatrixContext is populated with valid matrix profiles and that the constant
 *   NUM_MATRICES accurately represents the number of matrices in the context.
 *
 * Parameters:
 *   ctx - Pointer to the MatrixContext structure containing matrix profiles.
 *
 * Returns: None (void function).
 */
void printAllowedMatrixNames(const MatrixContext *ctx);

/*
 * Function: isValidMatrixName
 * Purpose: Checks if a given matrix name is valid within the context of predefined matrix profiles.
 * Detailed Description:
 *   This function iterates through the matrix profiles in a given MatrixContext to determine if
 *   the provided matrix name matches any of the predefined matrix names. It's used to validate
 *   if a given matrix name corresponds to any matrix within the context.
 *
 *   The function assumes that the MatrixContext structure (pointed by 'ctx') contains valid 
 *   matrix profiles and that the constant NUM_MATRICES correctly represents the total number of
 *   matrices in the context.
 *
 * Parameters:
 *   ctx - Pointer to the MatrixContext structure containing matrix profiles.
 *   matrixName - Pointer to a character array (string) representing the name of the matrix to be validated.
 *
 * Returns:
 *   A boolean value: 'true' if the matrix name is valid, 'false' otherwise.
 */
bool isValidMatrixName(const MatrixContext *ctx, const char *matrixName);

/*
 * Function: getMatrixEnumByName
 * Purpose: Retrieves the enum value of a matrix given its name.
 * Detailed Description:
 *   This function searches through the matrix profiles in a given MatrixContext to find
 *   a matrix that matches the provided name. Upon finding a match, it returns the enum
 *   value associated with that matrix. If no matching matrix is found, the function
 *   returns -1, indicating an invalid or nonexistent matrix name.
 * 
 *   The function assumes that the MatrixContext structure (pointed by 'ctx') contains valid
 *   matrix profiles and that the constant NUM_MATRICES correctly represents the total number
 *   of matrices in the context.
 *
 * Parameters:
 *   matrixName - Pointer to a character array (string) representing the name of the matrix.
 *   ctx - Pointer to the MatrixContext structure containing matrix profiles.
 *
 * Returns:
 *   The enum value of the matrix if found, or -1 if not found.
 */
MatrixEnum getMatrixEnumByName(const char *matrixName, const MatrixContext *ctx);

