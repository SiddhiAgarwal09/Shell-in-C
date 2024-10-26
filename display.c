#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "display.h"

void display_prompt() {
    // Get the username from the environment
    char* username = getenv("USER");
    if (username == NULL) {
        perror("Failed to get username");
        exit(EXIT_FAILURE);
    }

    // Get the hostname of the system
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("Failed to get hostname");
        exit(EXIT_FAILURE);
    }

    // Get the current working directory
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Failed to get current working directory");
        exit(EXIT_FAILURE);
    }

    // Get the home directory for the user
    char* home = getenv("HOME");
    if (home == NULL) {
        perror("Failed to get home directory");
        exit(EXIT_FAILURE);
    }

    // Replace home directory path with '~' in the current directory
    if (strstr(cwd, home) == cwd) {
        // Print as ~ if the current directory is inside the home directory
        printf("%s@%s:~%s$ ", username, hostname, cwd + strlen(home));
    } else {
        // Print the full current working directory
        printf("%s@%s:%s$", username, hostname, cwd);
    }

    fflush(stdout);
}
