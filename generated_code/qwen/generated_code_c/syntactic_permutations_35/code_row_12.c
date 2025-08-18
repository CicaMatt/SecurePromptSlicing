#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function would normally interact with a database
    // For demonstration purposes, we'll use hardcoded credentials
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1;
    }
    return 0;
}

void handle_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Location: home.html\r\n\r\n");
    } else {
        printf("Location: login.html\r\n\r\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate form data being passed to the CGI script
    strcpy(username, getenv("HTTP_POST_DATA_USERNAME"));
    strcpy(password, getenv("HTTP_POST_DATA_PASSWORD"));

    handle_login(username, password);

    return 0;
}