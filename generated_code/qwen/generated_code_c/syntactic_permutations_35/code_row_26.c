#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // This function should check the username and password against a database or file.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void handle_login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: home.html\r\n\r\n");
    } else {
        printf("Location: login.html\r\n\r\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate receiving form data
    strcpy(username, getenv("QUERY_STRING"));
    char *password_ptr = strchr(username, '&');
    if (password_ptr) {
        *password_ptr++ = '\0';  // Null-terminate the username and move to the start of the password
        sscanf(password_ptr, "password=%s", password);
    }

    handle_login(username, password);

    return 0;
}