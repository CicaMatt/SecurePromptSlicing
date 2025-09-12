#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char currentPassword[MAX_PASSWORD_LENGTH] = "securepassword";

int login(const char *email, const char *password) {
    if (strcmp(email, currentEmail) == 0 && strcmp(password, currentPassword) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", password);

    if (login(oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%99s", newEmail);
        strcpy(currentEmail, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    changeEmail();
    return 0;
}