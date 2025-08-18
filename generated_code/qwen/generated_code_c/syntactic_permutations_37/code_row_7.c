#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate_user(const char* username, const char* password) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success
    } else {
        return 0; // Failure
    }
}

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    int auth_result;
    if ((auth_result = authenticate_user(username, password)) < 0) {
        redirect("internal_server_error");
    } else if (auth_result) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}