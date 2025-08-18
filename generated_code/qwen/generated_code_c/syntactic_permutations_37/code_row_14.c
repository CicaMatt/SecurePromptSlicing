#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // Dummy authentication logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success
    } else {
        return 0; // Failure
    }
}

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\r\n\r\n");

    if (fgets(username, sizeof(username), stdin) == NULL ||
        fgets(password, sizeof(password), stdin) == NULL) {
        redirect("internal_server_error.html");
        return 1;
    }

    // Remove newline characters from input
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(username, password)) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}