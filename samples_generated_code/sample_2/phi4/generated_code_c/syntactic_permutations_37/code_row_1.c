#include <stdio.h>
#include <string.h>

#define MAX_INPUT 256

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];

    printf("Enter username: ");
    if (fgets(username, MAX_INPUT, stdin)) {
        // Remove newline character from fgets
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, MAX_INPUT, stdin)) {
        // Remove newline character from fgets
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    const char *validUsername = "user";
    const char *validPassword = "pass";

    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    return 0;
}