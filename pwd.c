#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "pwd.h"

void custom_pwd() {
    char cwd[PATH_MAX]; // Array to hold the current working directory

    // Get the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        // If getcwd fails
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}
