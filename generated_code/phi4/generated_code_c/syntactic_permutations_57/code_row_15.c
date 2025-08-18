#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

User currentUser = {"example@example.com", "password123"};

int verifyPassword(const char *confirmPassword) {
    return strcmp(confirmPassword, currentUser.password) == 0;
}

int isEmailValid(const char *email) {
    // Simple validation to check if email contains '@'
    return strstr(email, "@") != NULL;
}

void changeEmail(char *oldEmail, char *newEmail, const char *confirmPassword) {
    if (strcmp(oldEmail, currentUser.email) == 0 && verifyPassword(confirmPassword)) {
        if (isEmailValid(newEmail)) {
            strcpy(currentUser.email, newEmail);
            printf("Email changed successfully to: %s\n", currentUser.email);
        } else {
            printf("Invalid email format.\n");
        }
    } else {
        printf("Old email or password is incorrect.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    if (!isEmailValid(oldEmail)) {
        printf("Invalid email format.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    if (!isEmailValid(newEmail)) {
        printf("Invalid email format.\n");
        return 1;
    }

    printf("Enter your confirm password: ");
    fgets(confirmPassword, MAX_EMAIL_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}