#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.

    const char* valid_username = "admin";
    const char* valid_password = "password";

    return strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0;
}

void redirect_to_home() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=home.html\"></head></html>");
}

void redirect_to_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=login.html\"></head></html>");
}

int main(void) {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    // Simulate reading form data
    // In a real scenario, this would be done using CGI or another web framework
    strcpy(username, "admin");
    strcpy(password, "password");

    if (check_credentials(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}