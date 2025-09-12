#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        // Remove newline character from fgets
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin)) {
        // Remove newline character from fgets
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    const char *valid_username = "admin";
    const char *valid_password = "password123";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        redirectTo("success");
    } else if (username[0] != '\0' && password[0] != '\0') {
        redirectTo("cant_login");
    } else {
        redirectTo("internal_server_error");
    }

    return 0;
}