#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = check_credentials(username, password);

    if (result == 1) {
        redirect("success");
    } else if (result == 0) {
        redirect("cant_login");
    } else {
        redirect("internal_server_error");
    }

    return 0;
}