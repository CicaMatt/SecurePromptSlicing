#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // Dummy database for demonstration purposes
    const char *db_username = "admin";
    const char *db_password = "password123";

    if (strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0) {
        return 1; // Success
    } else {
        return 0; // Failure
    }
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real application, you would perform the actual redirection here.
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = 0; // Remove newline character
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = 0; // Remove newline character
    }

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