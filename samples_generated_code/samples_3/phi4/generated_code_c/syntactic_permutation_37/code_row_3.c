#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int checkCredentials(const char* username, const char* password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    if (checkCredentials(username, password)) {
        redirectTo("dashboard");
    } else {
        redirectTo("cant_login");
    }

    // Simulate an error condition for demonstration
    int errorOccurred = 0;
    if (errorOccurred) {
        redirectTo("internal_server_error");
    }

    return 0;
}