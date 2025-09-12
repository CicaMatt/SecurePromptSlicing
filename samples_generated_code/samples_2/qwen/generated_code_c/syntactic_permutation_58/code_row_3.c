#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(oldEmail, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(storedEmail, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}