#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "cd.h"

// Global variable to store the previous directory for 'cd -'
static char previous_directory[PATH_MAX] = "";
static char current_directory[PATH_MAX] = "";

void custom_cd(char *input) {
    // Update current directory before making changes
    if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
        perror("Failed to get current directory");
        return;
    }

    // If input is only "cd" or "cd ~", go to the home directory
    if (strcmp(input, "cd") == 0 || strcmp(input, "cd ~") == 0) {
        char *home_directory = getenv("HOME");
        if (home_directory == NULL) {
            perror("Failed to get home directory");
            return;
        }
        // Change directory to home
        if (chdir(home_directory) != 0) {
            perror("Failed to change directory to home");
        } else {
            // Update previous directory
            strcpy(previous_directory, current_directory);
        }
        return;
    }

    // If input is "cd ..", move one level up
    if (strcmp(input, "cd ..") == 0) {
        if (chdir("..") != 0) {
            perror("Failed to move one directory up");
        } else {
            // Update previous directory
            strcpy(previous_directory, current_directory);
        }
        return;
    }

    // If input is "cd -", go to the previous directory
    if (strcmp(input, "cd -") == 0) {
        if (strlen(previous_directory) == 0) {
            printf("No previous directory.\n");
            return;
        }
        // Print previous directory
        printf("%s\n", previous_directory);
        // Change to previous directory
        if (chdir(previous_directory) != 0) {
            perror("Failed to change to previous directory");
        } else {
            // Swap current and previous directories
            char temp[PATH_MAX];
            strcpy(temp, current_directory);
            strcpy(current_directory, previous_directory);
            strcpy(previous_directory, temp);
        }
        return;
    }

    // If the input is a directory, change to that directory
    if (strncmp(input, "cd ", 3) == 0) {
        char *new_directory = input + 3;  // Extract directory name after "cd "

        // Change the directory
        if (chdir(new_directory) != 0) {
            perror("Failed to change directory");
        } else {
            // Update previous directory
            strcpy(previous_directory, current_directory);
        }
        return;
    }

    // If input has more than one argument or is invalid
    printf("Invalid command or too many arguments.\n");
}
