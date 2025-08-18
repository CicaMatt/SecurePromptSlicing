#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void redirectToSession() {
    printf("Welcome! You have been redirected to your session.\n");
}

int main() {
    char correctUsername[MAX_LENGTH] = "user123";
    char correctPassword[MAX_LENGTH] = "pass456";
    
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_LENGTH, stdin);
    // Remove newline character
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, MAX_LENGTH, stdin);
    // Remove newline character
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectToSession();
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}