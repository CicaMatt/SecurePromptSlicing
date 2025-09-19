#include <stdio.h>
#include <string.h>

void redirectTo(const char *page) {
    printf("Redirecting to %s\n", page);
}

int main() {
    const char *validUsername = "user";
    const char *validPassword = "pass";

    char username[50];
    char password[50];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    return 0;
}