#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "password123";
    char enteredOldEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", enteredOldEmail);

    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredOldEmail, storedEmail) == 0 && strcmp(enteredPassword, storedPassword) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(storedEmail, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}