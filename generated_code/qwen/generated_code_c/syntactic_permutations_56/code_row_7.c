#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticate(const char *password, const char *enteredPassword) {
    return strcmp(password, enteredPassword) == 0;
}

void changeEmail(char *currentEmail, const char *oldEmail, const char *newEmail, const char *password, const char *confirmPassword) {
    if (strcmp(currentEmail, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }
    
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("Error: New email must be different from the old email.\n");
        return;
    }

    if (!authenticate(password, confirmPassword)) {
        printf("Error: Password confirmation failed.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully to %s\n", currentEmail);
}

int main() {
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char password[MAX_PASSWORD] = "password123"; // This should be hashed and stored securely in a real application
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);

    changeEmail(currentEmail, oldEmail, newEmail, password, confirmPassword);

    return 0;
}