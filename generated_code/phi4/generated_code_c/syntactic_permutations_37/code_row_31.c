#include <stdio.h>
#include <string.h>

// Simulated database entries
const char *valid_username = "user123";
const char *valid_password = "password123";

void redirectTo(const char *page) {
    printf("Redirecting to %s\n", page);
}

int checkLogin(const char *username, const char *password) {
    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (checkLogin(username, password)) {
        redirectTo("success");
    } else {
        int errorOccurred = 1; // Simulate no internal server errors for simplicity
        if (!errorOccurred) {
            redirectTo("internal_server_error");
        } else {
            redirectTo("cant_login");
        }
    }

    return 0;
}