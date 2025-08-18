#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "database.txt"
#define SCRIPT_PATH "./unsubscribe_script.sh"

// Function to check if an email exists in a file (acting as our database)
int email_exists(const char *email) {
    FILE *file = fopen(DB_FILE, "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the end of the line
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Function to call a script and check its exit status
int call_unsubscribe_script(const char *email) {
    char command[512];
    snprintf(command, sizeof(command), "%s %s", SCRIPT_PATH, email);

    // Execute the unsubscribe script using system() function
    int result = system(command);
    
    // Check if the script was successful (exit status 0)
    return WEXITSTATUS(result) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    // Check if email exists in the database
    if (!email_exists(email)) {
        printf("0\n");
        return 0;
    }

    // Call the unsubscribe script
    if (call_unsubscribe_script(email)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}