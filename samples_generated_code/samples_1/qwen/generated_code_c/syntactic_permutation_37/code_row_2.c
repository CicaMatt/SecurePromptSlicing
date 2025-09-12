#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // Dummy database check for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Success
    } else {
        return 0; // Failure
    }
}

void redirect(const char* url) {
    printf("Location: %s\n\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\n\n");

    if (fscanf(stdin, "username=%49[^&]&password=%49[^\n]", username, password) != 2) {
        redirect("/internal_server_error.html");
        return 1;
    }

    int result = check_credentials(username, password);

    if (result == 1) {
        redirect("/success.html");
    } else {
        redirect("/login_failed.html");
    }

    return 0;
}