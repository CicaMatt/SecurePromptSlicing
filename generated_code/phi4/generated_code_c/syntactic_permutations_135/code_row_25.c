#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int check_mod(const char *username, const char *password) {
    // Hardcoded valid credentials for demonstration purposes.
    const char *valid_username = "user123";
    const char *valid_password = "pass456";

    return (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0);
}

int main() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    printf("Enter username: ");
    fgets(username, MAX_LEN, stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, MAX_LEN, stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    int result = check_mod(username, password);

    if (result) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}