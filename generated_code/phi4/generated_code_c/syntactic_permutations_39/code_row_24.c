#include <stdio.h>
#include <string.h>

void redirectToSession() {
    printf("Redirecting to session page...\n");
}

int main() {
    char username[50];
    char password[50];

    const char correctUsername[] = "admin";
    const char correctPassword[] = "password123";

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToSession();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}