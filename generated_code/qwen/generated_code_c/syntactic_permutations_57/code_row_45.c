#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticate(const char* email, const char* password) {
    // Dummy authentication function
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(char* currentEmail, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (strcmp(currentEmail, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }

    if (!authenticate(oldEmail, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully. New email is %s\n", currentEmail);
}

int main() {
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);

    changeEmail(currentEmail, oldEmail, newEmail, confirmPassword);

    return 0;
}