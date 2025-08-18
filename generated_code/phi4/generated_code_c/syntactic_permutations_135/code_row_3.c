#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    // Hardcoded valid credentials for demonstration purposes.
    const char *valid_username = "user";
    const char *valid_password = "pass";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    if (strlen(password) > 0 && password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0';
    }

    int result = check_mod(username, password);

    if (result) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}