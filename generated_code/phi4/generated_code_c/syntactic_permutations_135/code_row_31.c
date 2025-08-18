#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int check_mod(const char *username, const char *password) {
    // Hardcoded correct credentials for demonstration purposes.
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    printf("Enter username: ");
    fgets(username, MAX_LEN, stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, MAX_LEN, stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    int result = check_mod(username, password);

    if (result) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}