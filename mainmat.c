/*
 * Main Matrix Manipulation Program Source File
 * --------------------------------------------
 * This C source file is a key component of the main matrix manipulation program, complementing the 
 * "mainmat.h" header. It implements the functions declared in the header, facilitating user interaction,
 * command processing, and execution of matrix operations in conjunction with the "Matrix Manipulation Library"
 * defined in "mymat.c" and "mymat.h".
 *
 * Implemented Functions:
 * - print_intro:                   Executes the introductory sequence for the Matrix Calculator Application, 
 *                                  displaying a welcoming message and a brief overview of available commands.
 * - print_outro:                   Handles the closing sequence, printing a farewell message when the application exits.
 * - isEmptyLine:                   Evaluates if a given string is empty or contains only whitespace, 
 *                                  aiding in input validation and processing.
 * - isValidCommand:                Checks whether a provided string matches any of the predefined valid commands.
 * - readAndProcessInstructions:    Main loop for reading and processing user instructions, 
 *                                  orchestrating the flow of matrix operations.
 * - processInstruction:            Interprets and executes individual matrix operation commands 
 *                                  based on user input.
 * - commandTypeReturn:             Identifies the CommandType associated with a given command string.
 * - readCommand:                   Extracts and validates a command from a given string, ensuring correct syntax.
 * - readInstruction:               Analyzes and processes a complete instruction line, 
 *                                  extracting necessary components for matrix operations.
 *
 * Usage:
 * This file should be compiled and linked with the main application that includes "mainmat.h". 
 * It is essential to ensure that the "Matrix Manipulation Library" from "mymat.c" and "mymat.h" 
 * is also included and linked, as this file relies on the structures, constants, and functions 
 * defined therein to operate correctly.
 *
 * Note:
 * The functions implemented here are designed to work within the constraints set by the "Matrix Manipulation Library".
 * This includes adhering to predefined matrix sizes, command formats, and error handling procedures.
 * Proper initialization of the 'MatrixContext' and consistent handling of matrices are crucial for 
 * the seamless operation of this program.
 * 
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mymat.h"
#include "mainmat.h"


/*
 * Function: main
 * Purpose: Entry point of the program.
 * Detailed Description:
 *   This is the main function from where the program execution begins. It first initializes
 *   the matrix context, then prints the introductory message. After that, it reads and processes
 *   user instructions. Depending on the success of processing instructions, it prints an outro
 *   message and exits with a status code indicating success (ERROR_NONE) or failure (ERROR_INVALID_INPUT).
 *
 * Returns: 
 *   ERROR_NONE on successful execution of instructions, ERROR_INVALID_INPUT otherwise.
 */
int main() {
    MatrixContext ctx;  /* Initialize the main matrix context */
    /* 
     * An array of MatrixProfile structures representing valid matrices.
     * This constant array is initialized with predefined matrix
     * identifiers and their corresponding string names.
     */
    const MatrixProfile validMatrices[NUM_MATRICES] = {
        {MAT_A, "MAT_A"},
        {MAT_B, "MAT_B"},
        {MAT_C, "MAT_C"},
        {MAT_D, "MAT_D"},
        {MAT_E, "MAT_E"},
        {MAT_F, "MAT_F"}
    };

    initMatrices(&ctx, validMatrices); /* Set up the matrices in the context */

    print_intro(&ctx);  /* Display introductory information and instructions */

    /* Read and process user instructions; this function likely involves
     * interaction with the user and performs various matrix operations */
    if (readAndProcessInstructions(&ctx)) {
        print_outro();  /* If instructions processed successfully, print the outro message */
        return (int)ERROR_NONE;             /* Return 0 indicating successful execution */
    } else {
        return (int)ERROR_INVALID_INPUT;    /* If there was an error in processing instructions, return -1 */
    }
}

void print_intro(const MatrixContext *ctx) {
    int command_idx; /* Variable for iterating over the command list */

    /* Print welcome message and application overview */
    printf("Welcome to Matrix Calculator Application\n");
    printf("=======================================\n\n");
    printf("This application allows you to perform various matrix operations.\n\n");
    
    /* Print the names of all matrices available in the application */
    printAllowedMatrixNames(ctx);

    /* Display the list of available commands with their descriptions */
    printf("Available Commands:\n");
    printf("-------------------\n");
    for (command_idx = 0; command_idx < NUM_COMMANDS; ++command_idx) {
        /* Print the name, syntax, and description of each command */
        printf("\n[%s]\n", validCommands[command_idx].commandName);
        printf("%s\n", validCommands[command_idx].commandSyntax);
        printf("%s\n", validCommands[command_idx].commandDescription);
    }
    /* Prompt for user input */
    printf("\n=======================================\n");
    printf("Please enter your instructions:\n");
}

void print_outro() {
    /* Print a friendly goodbye message and invite feedback */
    printf("\nThank you for using the Matrix Calculator Application!\n");
    printf("If you have any feedback or suggestions, please let us know.\n");
    printf("Goodbye and have a great day!\n\n");
}



bool isEmptyLine(const char *buffer) {
    int i = 0;  /* Index for iterating through the characters in the buffer */

    /* Loop through each character in the buffer */
    while (buffer[i] != '\0') {  /* Continue until the end of the string */
        /* Check if the current character is not a white-space character */
        if (!isspace((unsigned char) buffer[i])) {
            return false;  /* Return false if a non-white-space character is found */
        }
        i++;  /* Move to the next character */
    }
    return true;  /* Return true if only white-space characters or the line is empty */
}


bool readLine(char *buffer) {
    /*
    * readLine - Reads a line of text from standard input into a buffer.
    */
    int i = 0;  /* Index for placing characters into the buffer */
    char ch;    /* Variable to store each character read */

    /* Return false if the buffer pointer is NULL */
    if (buffer == NULL) 
        return false;

    /* Prompt for input */
    printf(">> ");

    /* Read characters until newline or EOF */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Store the character in the buffer if there's space (leave room for null terminator) */
        if (i < MAX_LINE_LENGTH - 1) {
            buffer[i++] = ch;
        }
    }

    buffer[i] = '\0';  /* Null-terminate the string in the buffer */

    /* Print the buffer content for redirection */
    printf("%s\n", buffer); 
    
    /* Return true if EOF is encountered, false otherwise */
    return (ch == EOF) ? true : false;
}

bool isValidCommand(const char *command) {
    int command_index; /* Variable for iterating over the command list */

    /* Loop through each valid command */
    for (command_index = 0; command_index < NUM_COMMANDS; command_index++) {
        /* Compare the current valid command with the provided command */
        if (!strcmp(validCommands[command_index].commandName, command)) {
            return true; /* Return true if a match is found */
        }
    }
    return false; /* Return false if no match is found after checking all valid commands */
}


CommandType commandTypeReturn(const char *command) {
    CommandType command_index; /* Variable for iterating over the command list */

    /* Loop through each valid command */
    for (command_index = 0; command_index < NUM_COMMANDS; command_index++) {
        /* Compare the current valid command with the provided command */
        if (!strcmp(validCommands[command_index].commandName, command)) {
            return command_index; /* Return the CommandType if a match is found */
        }
    }

    /* Print an error message if the command is not found */
    printf("Command not found");
    return -1; /* Return -1 indicating that the command was not found */
}



bool processInstruction(const char *command, 
                        char matrixNames[MAX_INPUT_MATRICES][MAX_MATRIX_NAME_LENGTH], 
                        double matrix_elements[ROWS * COLS], 
                        double *scalar,
                        MatrixContext *ctx) {
    /* Determine the CommandType from the command string */
    CommandType cmd = commandTypeReturn(command);

    /* Retrieve matrix enum values for the matrices involved */
    MatrixEnum mat1 = getMatrixEnumByName(matrixNames[FIRST_MATRIX], ctx);
    MatrixEnum mat2 = getMatrixEnumByName(matrixNames[SECOND_MATRIX], ctx);
    MatrixEnum mat3 = getMatrixEnumByName(matrixNames[THIRD_MATRIX], ctx);

    /* Process the command based on its type */
    switch (cmd) {
        case STOP: /* Stop the process */
            return true; 
            break;

        case READ_MAT: /* Read matrix data */
            readMatrix(ctx, matrixNames[FIRST_MATRIX], matrix_elements); 
            break;

        case PRINT_MAT: /* Print matrix */
            printMatrix(ctx, matrixNames[FIRST_MATRIX]); 
            break;

        case ADD_MAT: /* Add matrices */
            addMatrices(&ctx->matrices[mat1], &ctx->matrices[mat2], &ctx->matrices[mat3]);
            break;

        case SUB_MAT: /* Subtract matrices */
            subMatrices(&ctx->matrices[mat1], &ctx->matrices[mat2], &ctx->matrices[mat3]);
            break;

        case MUL_MAT: /* Perform matrix multiplication */
            if (mat2 != mat3 && mat1 != mat3) {
                multiplyMatrices(&ctx->matrices[mat1], &ctx->matrices[mat2], &ctx->matrices[mat3]);
            } else { /* Handle in-place multiplication */
                if (mat1 == mat3) {
                    multiplyMatricesInPlace(&ctx->matrices[mat2], &ctx->matrices[mat3]);
                    break;
                }  
                if (mat2 == mat3) {
                    multiplyMatricesInPlace(&ctx->matrices[mat1], &ctx->matrices[mat3]);
                    break;
                }
            }
            break;

        case MUL_SCALAR: /* Multiply matrix by scalar */
            multiplyScalar(&ctx->matrices[mat1], *scalar, &ctx->matrices[mat2]);
            break;

        case TRANS_MAT: /* Transpose matrix, either in-place or to another matrix */
            (mat1 == mat2) ?   
            transposeMatrixInPlace(&ctx->matrices[mat1]) : 
            transposeMatrix(&ctx->matrices[mat1], &ctx->matrices[mat2]);
            break;

        default:
            printf("Error: command not exist");
            break;
    }
    return false;
}

bool readAndProcessInstructions(MatrixContext *ctx) {
    char line[MAX_LINE_LENGTH];                                         /* Buffer to store each line read */
    char command[MAX_COMMAND_LENGTH];                                   /* Buffer to store parsed command */
    char matrixNames[MAX_INPUT_MATRICES][MAX_MATRIX_NAME_LENGTH] = {0}; /* Array to store matrix names */
    double matrix_elements[ROWS * COLS] = {0};                          /* Array to store matrix elements for 'read' command */
    bool isEOF = false;                                                 /* Flag to indicate end of file */
    bool isStop = false;                                                /* Flag to indicate 'stop' command */
    double scalar;                                                      /* Variable to store scalar value */
    InstructionError readInstructionResult;                             /* Variable to store the result of instruction reading */
    
    /* Main loop to read and process instructions */
    while (!isEOF) {
        isEOF = readLine(line); /* Reads a line from input and checks for EOF */

        /* Skip processing for empty lines */
        if (isEmptyLine(line)) {
            continue; /* Skip to the next iteration */
        }

        /* Read and parse the instruction */
        readInstructionResult = readInstruction(line, command, matrixNames, matrix_elements, &scalar, ctx);

        /* Process the instruction if no error occurred */
        if (readInstructionResult == NO_ERROR) {
            /* Process the instruction and check if it's a 'stop' command */
            isStop = processInstruction(command, matrixNames, matrix_elements, &scalar, ctx);
            if (isStop)
                return true;    /* Return true if 'stop' command is encountered */
        } else {
            /* Print error message if an error occurred while reading the instruction */
            printf("Error: %s\n", InstructionErrors[readInstructionResult].errorName);
        }

    }
    
    /* Check if EOF is reached without encountering 'stop' */
    if (isEOF && !isStop) {
        printf("Error: Unexpected End Of File. No 'stop' command found.\n");
    }
    return false; /* Return false if EOF is reached without 'stop' */
}


InstructionError readCommand(char **charPtr, char *command) {
    int index = 0;
    char *ptr = *charPtr;   /* Working pointer to the string */
    
    /* Skip initial white spaces */
    while (isspace(*ptr)) ptr++;    

    /* Read the command from the string */
    index = 0;
    while (!isspace(*ptr) && *ptr != '\0' && *ptr != ',') {
        command[index++] = *ptr++;  /* Copy characters to 'command' */
    }
    command[index] = '\0';          /* Null-terminate the command */

    /* Check if the command is valid */
    if (!isValidCommand(command)) {
        return UNDEFINED_COMMAND_NAME; /* Return error if command is not valid */
    }

    /* Command is valid, skip white spaces after the command */
    while (isspace(*ptr)) ptr++;
        
    /* Check for illegal comma placement after command */
    if (*ptr == ',') {
        return ILLEGAL_COMMA;   /* Return error if comma is found right after command */
    }
    *charPtr = ptr;             /* Update the original string pointer */
    return NO_ERROR;            /* Return NO_ERROR if everything is fine */
}


InstructionError readInstruction(char *line, 
                                 char *command, 
                                 char matrixNames[MAX_INPUT_MATRICES][MAX_MATRIX_NAME_LENGTH], 
                                 double matrix_elements[ROWS * COLS],
                                 double *scalar,
                                 MatrixContext *ctx) {
    char *charPtr;
    int index = 0;
    int matrix_name_saved = 0;
    char scalar_buffer[SCALAR_LENGTH] = {0};
    int scalar_index = 0;
    State currentState = ReadingMatrixName;
    CommandType cmd;
    InstructionError err;

    /* Return error if line is NULL */
    if (line == NULL) {
        return -1;
    }
    charPtr = line;

    /* Initialize scalar and matrix elements */
    *scalar = 0;
    for(index = 0; index < (ROWS * COLS); index++) {
        matrix_elements[index] = 0;
    }

    /* Read and validate the command */
    err = readCommand(&charPtr, command);
    if (err != NO_ERROR)
        return err;

    cmd = commandTypeReturn(command);   /* Determine the CommandType of the command */

    /* Special handling for STOP command */
    if (cmd == STOP)
        return (*charPtr == '\0') ? NO_ERROR : EXTRANEOUS_TEXT_AFTER_COMMAND;
    
    /* Main loop for parsing the instruction */
    while (*charPtr != '\0') {
        switch (currentState) {

            case ReadingMatrixName: /* Reading matrix names */
                index = 0;

                /* Read characters from charPtr until a space, comma, or end of string is reached */
                while (!isspace(*charPtr) && *charPtr != ',' && *charPtr != '\0') {
                    /* Store each character into the current matrix name */
                    matrixNames[matrix_name_saved][index++] = *charPtr++;
                }

                /* Null-terminate the current matrix name */
                matrixNames[matrix_name_saved][index] = '\0';

                /* Skip any white space after the matrix name */
                while (isspace(*charPtr)) charPtr++;

                /* Check if the matrix name is valid within the given context */
                if (!isValidMatrixName(ctx, matrixNames[matrix_name_saved]))
                    return UNDEFINED_MATRIX_NAME;   /* Return error if matrix name is not valid */
                
                matrix_name_saved++;    /* Increment the count of matrix names saved */

                /* Handle different command types that require matrix names */
                switch (cmd) {
                    case PRINT_MAT: 
                        /* For the 'print' command, there should be no extra text after the matrix name */
                        return (*charPtr == '\0') ? NO_ERROR : EXTRANEOUS_TEXT_AFTER_COMMAND;
                        break;
                    case TRANS_MAT:
                    case MUL_SCALAR:
                        /* For 'transpose' and 'multiply scalar', check if the required number of matrix names are read */
                        if (matrix_name_saved == 2) {
                            return (*charPtr == '\0') ? NO_ERROR : EXTRANEOUS_TEXT_AFTER_COMMAND;
                        }
                        break;
                    case ADD_MAT:
                    case SUB_MAT:
                    case MUL_MAT:
                        /* For 'add', 'subtract', and 'multiply', check if three matrix names are read */
                        if (matrix_name_saved == 3) {
                            return (*charPtr == '\0') ? NO_ERROR : EXTRANEOUS_TEXT_AFTER_COMMAND;
                        }  
                    default:
                        break;
                }
                /* After reading matrix name(s), transition to awaiting the next argument or comma */
                currentState = AvaitingArgument;
                break;

            case AvaitingArgument:
                /* Skip any leading white space before the next argument or comma */
                while (isspace(*charPtr)) charPtr++;

                /* Check if the next character is a comma */
                if (*charPtr == ',') {
                    charPtr++;  /* Move past the comma */

                    /* Skip any white space following the comma */
                    while (isspace(*charPtr)) charPtr++;
                    
                    /* Check for consecutive commas or improper comma usage */
                    if (*charPtr == ',')
                        return MULTIPLE_CONSECUTIVE_COMMAS; /* Two commas in a row indicate a syntax error */

                    /* Comma at the end of the line indicates incomplete command */
                    if (*charPtr == '\0'){
                        if (validCommands[cmd].numMatrices > matrix_name_saved) {
                            return MISSING_ARGUMENT;
                        } else {
                            return scalar_index ? EXTRANEOUS_TEXT_AFTER_COMMAND : MISSING_ARGUMENT;
                        }
                        /*return (validCommands[cmd].numMatrices > matrix_name_saved) ? MISSING_ARGUMENT : EXTRANEOUS_TEXT_AFTER_COMMAND;*/
                    }
                        /*return EXTRANEOUS_TEXT_AFTER_COMMAND;*/
                    
                    /* Determine the next state based on the command type */
                    switch (cmd) {
                        case READ_MAT:  /* or the 'read matrix' command, expect scalar values next */
                            currentState = ReadingScalar;
                            break;
                        case MUL_SCALAR: /* For 'multiply by scalar', transition based on whether a scalar value has been read */
                            currentState = scalar_index ? ReadingMatrixName : ReadingScalar;
                            break;
                        default:
                            /* For other commands, expect another matrix name */
                            currentState = ReadingMatrixName;
                            break;
                    }
                } else {
                    if (*charPtr == '\0') {
                        return (cmd == READ_MAT) ? NO_ERROR : MISSING_ARGUMENT;
                    }
                    /* If a comma is missing where expected, return an error */
                    return MISSING_COMMA;
                }
                break;

            case ReadingScalar: /* Reading a scalar value or matrix elements */
                index = 0;
                /* Read characters until a space, comma, or end of string is reached */
                while (!isspace(*charPtr) && *charPtr != ',' && *charPtr != '\0') {
                    /* Validate if the character is part of a valid number (digit, decimal point, or minus sign) */
                    if (isdigit(*charPtr) || *charPtr == '.' || *charPtr == '-') {
                        scalar_buffer[index++] = *charPtr++;    /* Store the valid character in the buffer */
                    } else {
                        /* If an invalid character is found, return an error indicating it's not a real number */
                        return (cmd == READ_MAT) ? ARGUMENT_NOT_REAL_NUMBER : ARGUMENT_NOT_SCALAR;
                    }
                }

                /* Null-terminate the scalar buffer and convert it to a double */
                scalar_buffer[index] = '\0';
                *scalar = atof(scalar_buffer);

                /* Handle commands that require scalar values */
                if ((cmd == READ_MAT)) {
                    /* If reading matrix elements, store the scalar value in the matrix_elements array */
                    if (scalar_index < (ROWS * COLS)) {
                        matrix_elements[scalar_index++] = *scalar;
                    }
                    /* Prepare for the next argument or end of command */
                    currentState = AvaitingArgument;
                }

                /*  If command is 'multiply by scalar', increment the scalar index and wait for the next argument */
                if (cmd == MUL_SCALAR) {
                    scalar_index++;
                    currentState = AvaitingArgument; 
                    if (*charPtr == '\0') {
                        return MISSING_ARGUMENT;
                    }
                }
                /* If the end of the string is reached, the command is successfully parsed */
                if (*charPtr == '\0') {
                    return NO_ERROR;
                }
                break;

            default:
                printf("Error: Unknown state");
                return -1;
                break;
        }
    }
    return MISSING_ARGUMENT; /* If the end of the string is reached without completing the instruction */
}