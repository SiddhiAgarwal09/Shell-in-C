#include <stdio.h>
#include <string.h>
#include <ctype.h>

void custom_echo(char *input) {
    while (isspace(*input)) input++;  // Trim leading spaces
    size_t len = strlen(input);
    while (len > 0 && isspace(input[len - 1])) {
        input[len - 1] = '\0';  // Trim trailing spaces
        len--;
    }

    // Check if the input is enclosed in double quotes
    if (input[0] == '"' && input[len - 1] == '"') {
        // If it's a quoted string, print it as is
        input[len - 1] = '\0';  // Remove the ending quote
        printf("%s\n", input + 1);  // Print the string without the starting quote
    } else {
        // If not quoted, process spaces
        char output[1024] = {0}; // To store the processed output
        int j = 0; // Index for output array
        int in_space = 1; // Flag to track spaces

        for (int i = 0; input[i] != '\0'; i++) {
            // Check if the current character is a space or a tab
            if (isspace(input[i])) {
                if (!in_space) {
                    // Add a single space to output if we were not in a space
                    output[j++] = ' ';
                    in_space = 1; 
                }
            } else {
                // Add the character to the output
                output[j++] = input[i];
                in_space = 0; 
            }
        }

        // Null-terminate the output string
        output[j] = '\0';

        printf("%s\n", output);
    }
}
