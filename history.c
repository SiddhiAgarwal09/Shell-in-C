#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

#define HISTORY_FILE ".custom_shell_history"
#define MAX_HISTORY_SIZE 20
#define DEFAULT_DISPLAY_COUNT 10

char *history[MAX_HISTORY_SIZE];  // Array to hold history
int history_count = 0;            // Current count of commands in history

// Load history from file when the shell starts
void load_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) {
        return;  // No history file yet
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0; 
        if (history_count < MAX_HISTORY_SIZE) {
            history[history_count++] = strdup(buffer);
        }
    }
    fclose(file);
}

// Save the command to history, ensuring FIFO order
void save_history(const char *command) {
    // Avoid saving if the command is the same as the previous one
    if (history_count > 0 && strcmp(history[history_count - 1], command) == 0) {
        return;
    }

    // Shift history if max size is reached
    if (history_count == MAX_HISTORY_SIZE) {
        free(history[0]);  // Remove oldest command
        for (int i = 1; i < MAX_HISTORY_SIZE; i++) {
            history[i - 1] = history[i];  // Shift each command up one position
        }
        history_count--;  // Decrement to make space for new command
    }

    // Add the new command at the end
    history[history_count++] = strdup(command);

    // Append the new command to the history file
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file == NULL) {
        perror("Error opening history file");
        return;
    }
    fprintf(file, "%s\n", command);
    fclose(file);
}

// Display the last `10` commands 
void display_history() {
    int start_index = (history_count > DEFAULT_DISPLAY_COUNT) ? history_count - DEFAULT_DISPLAY_COUNT : 0;

    for (int i = start_index; i < history_count; i++) {
        printf("%s\n", history[i]);
    }
}

void clear_history() {
    // Clear in-memory history
    for (int i = 0; i < history_count; i++) {
        free(history[i]);  // Free allocated memory for each command
        history[i] = NULL;
    }
    history_count = 0;

    // Clear history file on disk
    FILE *file = fopen(HISTORY_FILE, "w");
    if (file != NULL) {
        fclose(file);
    } else {
        perror("Error clearing history file");
    }
    printf("History cleared.\n");
}
