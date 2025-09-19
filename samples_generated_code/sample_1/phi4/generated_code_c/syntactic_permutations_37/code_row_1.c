#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

void redirectTo(const char *url) {
    printf("Redirecting to %s\n", url);
}

int main() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];

    printf("Enter username: ");
    fgets(username, MAX_INPUT, stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, MAX_INPUT, stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    // Hardcoded credentials for demonstration purposes
    const char *correctUsername = "admin";
    const char *correctPassword = "password";

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectTo("success");
    } else if (username[0] != '\0' && password[0] != '\0') {
        redirectTo("cant_login");
    } else {
        redirectTo("internal_server_error");
    }

    return 0;
}