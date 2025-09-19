#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function would typically query a database.
    // For demonstration, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void redirect_to_home() {
    printf("Content-type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/home.html\"></head></html>");
    exit(0);
}

void redirect_to_login() {
    printf("Content-type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/login.html\"></head></html>");
    exit(0);
}

int main() {
    char *username = getenv("HTTP_POST_USERNAME");
    char *password = getenv("HTTP_POST_PASSWORD");

    if (username == NULL || password == NULL) {
        printf("Content-type: text/html\n\n");
        printf("<h1>Invalid request</h1>");
        return 1;
    }

    if (check_credentials(username, password)) {
        redirect_to_home();
    } else {
        redirect_to_login();
    }

    return 0;
}