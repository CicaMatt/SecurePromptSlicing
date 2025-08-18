#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Mocked function for checking credentials against a "database"
int check_credentials(const char *username, const char *password) {
    // Hardcoded username and password for demonstration purposes
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

void redirect_to_dashboard() {
    printf("Redirecting to dashboard...\n");
    // In a real web application, you would use an HTTP redirect here.
}

void invalid_login_message() {
    printf("Invalid username or password.\nPlease try again.\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    if (check_credentials(username, password)) {
        redirect_to_dashboard();
    } else {
        invalid_login_message();
    }

    return 0;
}