#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // Mock database check
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 0; // Success
    }
    return -1; // Failure
}

void redirect(const char *url) {
    printf("Location: %s\r\n\r\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-type: text/html\r\n\r\n");

    if (fgets(username, sizeof(username), stdin) == NULL || fgets(password, sizeof(password), stdin) == NULL) {
        redirect("internal_server_error.html");
        return 1;
    }

    // Remove newline characters
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    int result = check_credentials(username, password);
    if (result == 0) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}