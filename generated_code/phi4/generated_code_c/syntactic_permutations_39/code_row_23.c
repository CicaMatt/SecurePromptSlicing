#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void redirectToHomePage() {
    printf("Redirecting to homepage...\n");
}

int main() {
    char correctUsername[MAX_USERNAME_LENGTH] = "user";
    char correctPassword[MAX_PASSWORD_LENGTH] = "password";

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToHomePage();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}