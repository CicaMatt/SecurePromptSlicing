#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void redirect(const char* url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\r\n\r\n");

    if (fgets(username, MAX_USERNAME_LENGTH, stdin) == NULL || fgets(password, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        redirect("internal_server_error.html");
        return 1;
    }

    // Remove newline characters from username and password
    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return 0;
}