#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

char* check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];

    // Example usage: normally you'd get these from a URL or user input
    printf("Enter username: ");
    fgets(username, MAX_INPUT_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_INPUT_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    char* result = check_mod(username, password);

    printf("Authentication %s\n", result);

    return 0;
}