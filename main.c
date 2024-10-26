#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "history.h"

int main() {
    // Load command history at the start
    load_history();

    while (1) {
        display_prompt();

        // Read user input
        char input[1024];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = 0;  // Remove newline character if present

        // Save the command in history (skip if the command is empty)
        if (strlen(input) > 0) {
            save_history(input);
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        if (strncmp(input, "echo ", 5) == 0) {
            custom_echo(input + 5); // Skip the "echo " part
        } else if (strcmp(input, "pwd") == 0) {
            custom_pwd();  // Call the custom pwd function
        } else if (strncmp(input, "cd", 2) == 0) {
            custom_cd(input);  // Handle cd command
        } else if (strcmp(input, "history") == 0) {
            display_history();  // Show command history
        } else if (strcmp(input, "clear_history") == 0) {
            clear_history();  // Clear command history
        } else {
            printf("Command not recognized: %s\n", input);
        }
    }

    return 0;
}
