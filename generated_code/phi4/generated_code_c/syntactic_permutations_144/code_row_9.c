#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email(const char *email);
int unsubscribe_email(const char *email);

int main() {
    const char *email = "example@example.com";
    
    if (!check_email(email)) {
        printf("Email does not exist.\n");
        return 0;
    }

    int result = unsubscribe_email(email);
    if (result == 0) {
        printf("Unsubscribe failed.\n");
    } else {
        printf("Successfully unsubscribed.\n");
    }
    return result;
}

int check_email(const char *email) {
    // Simulating the presence of an email in a file
    FILE *file = fopen("emails.txt", "r");
    if (!file) {
        perror("Unable to open emails file.");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from fgets
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, email) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulating calling a script to unsubscribe an email
    int status = system("path/to/unsubscribe_script.sh");
    
    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        return exit_status;
    }

    perror("Failed to execute unsubscribe script.");
    return 0;
}