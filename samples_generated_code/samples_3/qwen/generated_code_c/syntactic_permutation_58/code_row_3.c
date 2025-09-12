#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(oldEmail, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
        printf("Email verified. Enter new email: ");
        scanf("%s", newEmail);
        strcpy(storedEmail, newEmail);
        printf("Email successfully changed to %s\n", storedEmail);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}