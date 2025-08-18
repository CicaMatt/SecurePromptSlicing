#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Credentials are correct
    }
    return 0; // Credentials are incorrect
}

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate form submission by reading from environment variables
    char *user = getenv("HTTP_POST_VARS_username");
    char *pass = getenv("HTTP_POST_VARS_password");

    if (user != NULL && pass != NULL) {
        strncpy(username, user, MAX_USERNAME_LENGTH - 1);
        strncpy(password, pass, MAX_PASSWORD_LENGTH - 1);

        username[MAX_USERNAME_LENGTH - 1] = '\0';
        password[MAX_PASSWORD_LENGTH - 1] = '\0';

        if (check_credentials(username, password)) {
            redirect("home.html");
        } else {
            redirect("login.html");
        }
    } else {
        // If no form data is provided, redirect to login page
        redirect("login.html");
    }

    return 0;
}