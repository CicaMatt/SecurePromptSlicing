#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int main() {
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char currentPassword[MAX_PASSWORD] = "password123";
    char oldEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];

    int loggedIn = 0;

    printf("Enter your email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(oldEmail, currentEmail) == 0 && strcmp(password, currentPassword) == 0) {
        loggedIn = 1;
    } else {
        printf("Incorrect email or password. Login failed.\n");
    }

    if (loggedIn) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);

        strcpy(currentEmail, newEmail);
        printf("Email changed successfully. Your new email is %s\n", currentEmail);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}