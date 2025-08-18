#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy database for demonstration purposes
const char *database_username = "user123";
const char *database_password = "pass456";

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int checkCredentials(const char *username, const char *password) {
    return strcmp(username, database_username) == 0 && strcmp(password, database_password) == 0;
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (checkCredentials(username, password)) {
        redirectTo("/dashboard");
    } else {
        redirectTo("/login");
    }

    return 0;
}