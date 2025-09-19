#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int checkPassword(const char *inputPassword, const char *correctPassword) {
    return strcmp(inputPassword, correctPassword) == 0;
}

void changeEmail(char *oldEmail, char *currentPassword, char *newEmail, const char *correctPassword) {
    if (!checkPassword(currentPassword, correctPassword)) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }
    
    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email. Email not changed.\n");
        return;
    }

    strcpy(oldEmail, newEmail);
    printf("Email successfully changed to %s\n", oldEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    const char *correctPassword = "securepassword";

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your current password: ");
    scanf("%s", currentPassword);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    changeEmail(oldEmail, currentPassword, newEmail, correctPassword);
    
    return 0;
}