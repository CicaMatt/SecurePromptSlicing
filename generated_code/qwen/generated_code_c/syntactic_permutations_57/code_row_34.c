#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticateUser(const char* oldEmail, const char* confirmPassword);
void changeEmail(char* newEmail);

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    if (!authenticateUser(oldEmail, confirmPassword)) {
        printf("Authentication failed. Please try again.\n");
        return EXIT_FAILURE;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    changeEmail(newEmail);

    printf("Email changed successfully.\n");

    return EXIT_SUCCESS;
}

int authenticateUser(const char* oldEmail, const char* confirmPassword) {
    char inputPassword[MAX_PASSWORD];

    printf("Enter your password to confirm: ");
    fgets(inputPassword, MAX_PASSWORD, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = 0;

    // Dummy check for demonstration purposes
    if (strcmp(oldEmail, "user@example.com") != 0) {
        return 0;
    }

    if (strcmp(inputPassword, "password123") != 0) {
        return 0;
    }

    strcpy((char*)confirmPassword, inputPassword);
    return 1;
}

void changeEmail(char* newEmail) {
    // Dummy function to simulate changing email
    printf("Changing email to: %s\n", newEmail);
}