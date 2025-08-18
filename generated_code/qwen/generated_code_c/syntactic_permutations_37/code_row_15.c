#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This is a placeholder for database checking logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void redirect_to(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real web server environment, you would use HTTP headers for redirection
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

    int login_success = check_credentials(username, password);

    if (login_success) {
        redirect_to("success");
    } else {
        redirect_to("cant_login");
    }

    return 0;
}