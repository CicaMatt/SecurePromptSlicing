#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *output;
    char username[256];
    char command[300];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    output = fopen("output.txt", "w");
    if (output == NULL) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }

    snprintf(command, sizeof(command), "getent passwd %s", username);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        fclose(output);
        return EXIT_FAILURE;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, output);
    }

    pclose(fp);
    fclose(output);

    return EXIT_SUCCESS;
}