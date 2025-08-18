#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int check_credentials(const char *username, const char *password) {
    // This function should interact with a database to verify credentials.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void redirect_to_home() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=home.html\"></head></html>");
}

void redirect_to_login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=login.html\"></head></html>");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    // Simulate reading from form data
    if (fscanf(stdin, "username=%[^&]&password=%s", username, password) != 2) {
        redirect_to_login();
        return 1;
    }

    if (check_credentials(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}