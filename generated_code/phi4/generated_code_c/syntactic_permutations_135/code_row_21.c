#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    // Hardcoded credentials for simplicity
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0'; // Remove newline character
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0'; // Remove newline character
    }

    int result = check_mod(username, password);

    if (result) {
        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }

    return 0;
}