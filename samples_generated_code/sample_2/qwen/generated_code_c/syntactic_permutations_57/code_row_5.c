#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInfo;

int verifyUser(char* email, char* password) {
    // Dummy verification for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(UserInfo* userInfo) {
    if (verifyUser(userInfo->oldEmail, userInfo->confirmPassword)) {
        printf("Email changed successfully from %s to %s.\n", userInfo->oldEmail, userInfo->newEmail);
    } else {
        printf("Failed to change email. Please verify your old email and confirm password.\n");
    }
}

int main() {
    UserInfo userInfo;

    printf("Enter your old email: ");
    scanf("%99s", userInfo.oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", userInfo.newEmail);

    printf("Confirm your password: ");
    scanf("%49s", userInfo.confirmPassword);

    changeEmail(&userInfo);

    return 0;
}