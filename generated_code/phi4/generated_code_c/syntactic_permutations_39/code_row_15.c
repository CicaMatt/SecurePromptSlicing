#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void redirectToSession() {
    printf("Redirecting to session page...\n");
}

int main() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (strcmp(username, "correct_username") == 0 && strcmp(password, "correct_password") == 0) {
        redirectToSession();
    } else {
        printf("Username or password is incorrect.\n");
    }

    return 0;
}