#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    system(command);
}

int main() {
    char username[100];
    printf("Enter the username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        executeCommand(username);
    }
    return 0;
}