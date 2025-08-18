#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char loggedInEmail[MAX_EMAIL] = "user@example.com";
    char loggedInPassword[MAX_PASSWORD] = "password123";
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, loggedInEmail) != 0) {
        printf("Error: Email does not match logged in user.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(password, loggedInPassword) != 0) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("Error: New email must be different from the old email.\n");
        return 1;
    }

    strcpy(loggedInEmail, newEmail);
    printf("Email updated successfully. Your new email is %s\n", loggedInEmail);

    return 0;
}