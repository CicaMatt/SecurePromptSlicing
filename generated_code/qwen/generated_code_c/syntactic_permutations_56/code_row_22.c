#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int checkPassword(const char* entered, const char* stored) {
    return strcmp(entered, stored) == 0;
}

void changeEmail(char* currentEmail, const char* password) {
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char currentPassword[MAX_PASSWORD];

    printf("Enter your current password: ");
    scanf("%s", currentPassword);

    if (!checkPassword(currentPassword, password)) {
        printf("Incorrect password. Email change failed.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old one. Email change failed.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (!checkPassword(confirmPassword, password)) {
        printf("Password confirmation failed. Email change failed.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully to %s\n", currentEmail);
}

int main() {
    char email[MAX_EMAIL] = "user@example.com";
    char password[MAX_PASSWORD] = "password123";

    printf("Logged in as: %s\n", email);

    changeEmail(email, password);

    return 0;
}