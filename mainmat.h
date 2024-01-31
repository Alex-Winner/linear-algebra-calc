/*
 * Main Matrix Manipulation Program Header
 * ---------------------------------------
 * This C header file is part of the main matrix manipulation program and works in conjunction with the
 * "Matrix Manipulation Library" provided by "mymat.c". It defines the necessary constants, enumerations,
 * and function declarations for handling user inputs, processing commands, and managing matrix operations
 * within a predefined context, 'MatrixContext'.
 *
 * Constants:
 * - MAX_COMMAND_LENGTH:        Maximum length for a command string.
 * - MAX_INPUT_MATRICES:        Maximum number of input matrices allowed.
 * - MAX_LINE_LENGTH:           Maximum length for an input line.
 * - SCALAR_LENGTH:             Maximum length for a scalar value string.
 * - MAX_MATRIX_NAME_LENGTH:    Maximum length for a matrix name string.
 * 
 * Enumerations:
 * - State:                     Enumeration to represent different states during command parsing.
 * - CommandType:               Enumeration for various matrix operation commands.
 * - CommandMatrixArguments:    Enumeration for matrix argument positions in commands.
 * - InstructionError:          Enumeration for different types of errors in instruction processing.
 * - ErrorCode:                 Enumeration to represent different error codes for the OS.
 *
 * Structures:
 * - CommandProfile:            Structure to define the profile of a command.
 * - InstructionErrorProfile:   Structure to define the profile of an instruction error.
 *
 * Core Functions:
 * - print_intro:                   Prints the introductory message and available commands for the Matrix Calculator Application.
 * - print_outro:                   Prints the closing message for the Matrix Calculator Application.
 * - isEmptyLine:                   Checks if a given string (line) contains only white-space characters or is empty.
 * - isValidCommand:                Checks if a given string is a valid command.
 * - readAndProcessInstructions:    Reads and processes user instructions for matrix operations.
 * - processInstruction:            Processes a matrix operation command and executes the corresponding action.
 * - commandTypeReturn:             Determines the CommandType of a given command string.
 * - readCommand:                   Reads and validates a command from a string.
 * - readInstruction:               Parses and validates a matrix operation instruction from a string.
 * 
 * 
 * 
 * Usage:
 * To use these functionalities, include this header file in your C program. These functions are designed to
 * work with the structures and operations defined in "mymat.c" and "mymat.h". Ensure proper initialization
 * and handling of the 'MatrixContext' structure for correct operation and data management.
 *
 * Note:
 * This program expects certain pre-defined constants and structures (like 'MatrixContext') from the
 * "Matrix Manipulation Library". The interaction between this program and the library is crucial for
 * the successful execution of matrix operations and command processing.
 */


/* Maximum length for a command string */
#define MAX_COMMAND_LENGTH 16

/* Maximum number of input matrices allowed */
#define MAX_INPUT_MATRICES 3

/* Maximum length for an input line */
#define MAX_LINE_LENGTH 256

/* Maximum length for a scalar value string */
#define SCALAR_LENGTH 32

/* Maximum length for a matrix name string */
#define MAX_MATRIX_NAME_LENGTH 16

/* Enumeration to represent different error codes for the OS */
typedef enum {
    ERROR_NONE = 0,   
    ERROR_INVALID_INPUT = -1
} ErrorCode;


/* Enumeration to represent different states during command parsing */
typedef enum {
    AvaitingArgument,   /* Waiting for an argument in the input command */
    ReadingMatrixName,  /* Reading the name of a matrix in the input command */
    ReadingScalar       /* Reading a scalar value in the input command */
} State;

/* Enumeration to represent different command types */
typedef enum {
    STOP,            /* Stop the program */
    READ_MAT,        /* Read a matrix from user input */
    PRINT_MAT,       /* Print a matrix */
    ADD_MAT,         /* Add two matrices */
    SUB_MAT,         /* Subtract two matrices */
    MUL_MAT,         /* Multiply two matrices */
    MUL_SCALAR,      /* Multiply a matrix by a scalar */
    TRANS_MAT,       /* Transpose a matrix */
    NUM_COMMANDS     /* Sentinel value for the number of commands */
} CommandType;


/* Structure to define the profile of a command */
typedef struct {
    CommandType commandType;        /* Enum representation*/
    const char *commandName;        /* Name of the command */
    const char *commandDescription; /* Description of the command's purpose */
    const char *commandSyntax;      /* Syntax for using the command */
    int numMatrices;                /* Number of matrices needed */
} CommandProfile;


/* Enumeration to represent different matrix argument positions in a command */
typedef enum {
    FIRST_MATRIX,   /* First matrix in the command */
    SECOND_MATRIX,  /* Second matrix in the command */
    THIRD_MATRIX    /* Third matrix in the command */
} CommandMatrixArguments;

/* Array of valid commands and their expected number of matrix arguments */
const CommandProfile validCommands[NUM_COMMANDS] = {
    {STOP, "stop", 
    "Description: Exit the application.", 
    "Syntax: stop",
    0},
    
    {READ_MAT, "read_mat", 
    "Description: Read a matrix and store its values.",
    "Syntax: read_mat <matrix_name>, <arg1>, <arg2>, ...",
    1},

    {PRINT_MAT, "print_mat", 
    "Description: Print the contents of a matrix.",
    "Syntax: print_mat <matrix_name>",
    1},

    {ADD_MAT, "add_mat", 
    "Description: Add two matrices.",
    "Syntax: add_mat <matrix1_name>, <matrix2_name>, <result_matrix_name>", 
    3},

    {SUB_MAT, "sub_mat", 
    "Description: Subtract one matrix from another.",
    "Syntax: sub_mat <matrix1_name>, <matrix2_name>, <result_matrix_name>", 
    3},

    {MUL_MAT, "mul_mat", 
    "Description: Multiply two matrices.",
    "Syntax: mul_mat <matrix1_name>, <matrix2_name>, <result_matrix_name>", 
    3},

    {MUL_SCALAR, "mul_scalar", 
    "Description: Multiply a matrix by a scalar value.",
    "Syntax: mul_scalar <matrix_name>, <scalar>, <result_matrix_name>", 
    2},


    {TRANS_MAT, "trans_mat", 
    "Description: Transpose a matrix.",
    "Syntax: trans_mat <matrix_name>, <result_matrix_name>", 
    2}
};


/* Enumeration to represent different error types during instruction processing */
typedef enum {
    NO_ERROR,                           /* No error occurred */
    UNDEFINED_MATRIX_NAME,              /* Matrix name in the instruction is undefined */
    UNDEFINED_COMMAND_NAME,             /* Command name in the instruction is undefined */
    ARGUMENT_NOT_REAL_NUMBER,           /* An argument in the instruction is not a real number */
    EXTRANEOUS_TEXT_AFTER_COMMAND,      /* Extraneous text found after a valid command */
    MISSING_ARGUMENT,                   /* Missing argument in the instruction */
    ILLEGAL_COMMA,                      /* An illegal comma was encountered in the instruction */
    MISSING_COMMA,                      /* A required comma is missing in the instruction */
    MULTIPLE_CONSECUTIVE_COMMAS,        /* Multiple consecutive commas found in the instruction */
    ARGUMENT_NOT_SCALAR,                /* An argument in the instruction is not a scalar value */
    NUM_ERRORS                          /* Sentinel value for the number of Errors */
} InstructionError;


/* Structure to define the profile of an instruction error */
typedef struct {
    InstructionError errorType; /* Type of the instruction error */
    const char *errorName;      /* Name or description of the error */
} InstructionErrorProfile;

/* Array of instruction error profiles for mapping error types to their names or descriptions */
const InstructionErrorProfile InstructionErrors[NUM_ERRORS] = {
    {NO_ERROR, "No error"},                                                     /* No error occurred */
    {UNDEFINED_MATRIX_NAME, "Undefined matrix name"},                           /* Matrix name in the instruction is undefined */
    {UNDEFINED_COMMAND_NAME, "Undefined command name"},                         /* Command name in the instruction is undefined */
    {ARGUMENT_NOT_REAL_NUMBER, "Argument is not a real number"},                /* An argument in the instruction is not a real number */
    {EXTRANEOUS_TEXT_AFTER_COMMAND, "Extraneous text after end of command"},    /* Extraneous text found after a valid command */
    {MISSING_ARGUMENT, "Missing argument"},                                     /* Missing argument in the instruction */
    {ILLEGAL_COMMA, "Illegal comma"},                                           /* An illegal comma was encountered in the instruction */
    {MISSING_COMMA, "Missing comma"},                                           /* A required comma is missing in the instruction */
    {MULTIPLE_CONSECUTIVE_COMMAS, "Multiple consecutive commas"},               /* Multiple consecutive commas found in the instruction */
    {ARGUMENT_NOT_SCALAR, "Argument is not a scalar"}                           /* An argument in the instruction is not a scalar value */
};


/*
 * Function: readLine
 * Purpose: Reads a line of text from standard input into a buffer.
 * Detailed Description:
 *   This function reads characters from standard input (usually the console) until it encounters
 *   a newline character ('\n') or EOF (End Of File). It stores the characters in a provided buffer,
 *   ensuring not to exceed the buffer's capacity. The function null-terminates the string in the buffer
 *   and also handles the case where the buffer pointer is NULL.
 *
 * Parameters:
 *   buffer - Pointer to a character array where the input line will be stored.
 *
 * Returns:
 *   true if EOF is encountered; false otherwise.
 */
bool readLine(char *buffer);

/*
 * Function: print_intro
 * Purpose: Prints the introductory message and available commands for the Matrix Calculator Application.
 * Detailed Description:
 *   This function displays a welcome message and provides a brief overview of the application's capabilities.
 *   It lists all available matrix names stored in the MatrixContext and then proceeds to display all
 *   valid commands that the user can execute, including their syntax and descriptions.
 *   It assumes that the list of valid commands and their descriptions are stored in an array validCommands
 *   and that the constant NUM_COMMANDS accurately represents the number of available commands.
 *
 * Parameters:
 *   ctx - Pointer to the MatrixContext structure containing matrix profiles.
 *
 * Returns: None (void function).
 */
void print_intro(const MatrixContext *ctx);


/*
 * Function: print_outro
 * Purpose: Prints the closing message for the Matrix Calculator Application.
 * Detailed Description:
 *   This function displays a farewell message to the user at the end of the application's execution. 
 *   It thanks the user for using the application, invites feedback or suggestions, and wishes them well.
 *   This function enhances user experience by providing a friendly and courteous conclusion to the interaction.
 *
 * Returns: None (void function).
 */
void print_outro();


/*
 * Function: isEmptyLine
 * Purpose: Checks if a given string (line) contains only white-space characters or is empty.
 * Detailed Description:
 *   This function iterates through each character in the input string (buffer) and checks
 *   if it contains any non-white-space characters. If it finds any non-white-space character,
 *   the function returns false, indicating that the line is not empty. If it only finds
 *   white-space characters or reaches the end of the string without finding any non-white-space
 *   characters, it returns true, indicating that the line is empty or contains only white-space.
 *
 * Parameters:
 *   buffer - Pointer to a character array (string) representing the line to be checked.
 *
 * Returns: 
 *   true if the line is empty or contains only white-space characters; false otherwise.
 */
bool isEmptyLine(const char *buffer);


/*
 * Function: isValidCommand
 * Purpose: Checks if a given string is a valid command.
 * Detailed Description:
 *   This function iterates through a predefined list of valid commands and compares each
 *   with the provided string (command). If a match is found, it returns true, indicating
 *   the command is valid. If no match is found after checking all the predefined commands,
 *   it returns false, indicating the command is invalid. The function assumes that the list
 *   of valid commands is stored in an array validCommands and that NUM_COMMANDS accurately
 *   represents the number of valid commands.
 *
 * Parameters:
 *   command - Pointer to a character array (string) representing the command to be validated.
 *
 * Returns:
 *   true if the command is valid; false otherwise.
 */
bool isValidCommand(const char *command);


/*
 * Function: readAndProcessInstructions
 * Purpose: Reads and processes user instructions for matrix operations.
 * Detailed Description:
 *   This function continuously reads lines of instructions, skipping empty lines and comments,
 *   until it encounters a 'stop' command or reaches the end of file (EOF). Each valid instruction
 *   is parsed and processed. If an error occurs during instruction parsing, an error message is displayed.
 *   The function assumes that the provided MatrixContext (ctx) is properly initialized and ready for
 *   matrix operations.
 *
 * Parameters:
 *   ctx - Pointer to the MatrixContext structure containing matrix data and profiles.
 *
 * Returns:
 *   true if the 'stop' command is processed; false if EOF is reached without encountering 'stop'.
 */
bool readAndProcessInstructions(MatrixContext *ctx);


/*
 * Function: processInstruction
 * Purpose: Processes a matrix operation command and executes the corresponding action.
 * Detailed Description:
 *   This function takes a command string and processes it by executing the corresponding matrix operation.
 *   It identifies the command type and matrix names involved, then performs the operation specified by the 
 *   command. Operations include reading, printing, and various arithmetic operations on matrices.
 *
 *   The function assumes that the command and matrix names are valid, and that the matrix elements and scalar
 *   values provided are correct for the operation. It handles different commands through a switch statement,
 *   calling appropriate functions for each command.
 *
 * Parameters:
 *   command - Pointer to a string representing the command to be processed.
 *   matrixNames - Array of strings representing the names of matrices involved in the operation.
 *   matrix_elements - Array of doubles representing matrix elements (for reading matrix data).
 *   scalar - Pointer to a double representing a scalar value (for scalar multiplication).
 *   ctx - Pointer to the MatrixContext structure containing matrix data.
 *
 * Returns:
 *   true if the command is STOP; false otherwise.
 */
bool processInstruction(const char *command, 
                        char matrixNames[MAX_INPUT_MATRICES][MAX_MATRIX_NAME_LENGTH], 
                        double matrix_elements[ROWS * COLS], 
                        double *scalar,
                        MatrixContext *ctx);


/*
 * Function: commandTypeReturn
 * Purpose: Determines the CommandType of a given command string.
 * Detailed Description:
 *   This function searches through a list of valid commands and matches the provided command string.
 *   If a match is found, it returns the CommandType (typically an enum or integer representing the command).
 *   If the command is not found, it prints an error message and returns a special value (-1 in this case),
 *   indicating that the command is invalid or not found.
 *
 *   The function assumes that validCommands is an array of structures containing command names and their
 *   corresponding CommandType, and that NUM_COMMANDS accurately represents the number of available commands.
 *
 * Parameters:
 *   command - Pointer to a character array (string) representing the command whose CommandType is to be determined.
 *
 * Returns:
 *   CommandType corresponding to the command if found; -1 if the command is not found.
 */
CommandType commandTypeReturn(const char *command);


/*
 * Function: readCommand
 * Purpose: Reads and validates a command from a string.
 * Detailed Description:
 *   This function extracts a command from the provided string, skipping leading white spaces.
 *   It reads characters until it encounters a space, a null character, or a comma, indicating the end of the command.
 *   After reading the command, it checks its validity. If the command is not valid, it returns an error.
 *   If the command is valid but followed directly by a comma, it also returns an error.
 *
 * Parameters:
 *   charPtr - Pointer to a pointer to the string from which the command is read.
 *   command - Pointer to a character array where the read command will be stored.
 *
 * Returns:
 *   NO_ERROR if the command is read and validated successfully,
 *   UNDEFINED_COMMAND_NAME if the command is not valid,
 *   ILLEGAL_COMMA if a comma is improperly placed after the command.
 */
InstructionError readCommand(char **charPtr, char *command);


/*
 * Function: readInstruction
 * Purpose: Parses and validates a matrix operation instruction from a string.
 * Detailed Description:
 *   This function takes a line of text and extracts the command, matrix names, scalar value, and matrix elements
 *   based on the command type. It handles different commands and checks for various errors like invalid matrix names,
 *   incorrect argument types, missing commas, and more. The function uses a state machine approach for parsing,
 *   transitioning between different states based on the input received and the command being processed.
 *
 * Parameters:
 *   line - Pointer to a string containing the instruction to be parsed.
 *   command - Pointer to a char array where the parsed command will be stored.
 *   matrixNames - 2D array of chars to store the names of matrices involved in the operation.
 *   matrix_elements - Array of doubles to store matrix elements if needed for the command.
 *   scalar - Pointer to a double to store the scalar value if needed for the command.
 *   ctx - Pointer to the MatrixContext structure containing matrix data and profiles.
 *
 * Returns:
 *   An InstructionError enum indicating the status of the instruction reading process.
 */
InstructionError readInstruction(char *line, 
                                 char *command, 
                                 char matrixNames[MAX_INPUT_MATRICES][MAX_MATRIX_NAME_LENGTH], 
                                 double matrix_elements[ROWS * COLS], 
                                 double *scalar, 
                                 MatrixContext *ctx);