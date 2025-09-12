#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100

typedef struct {
    char currentEmail[MAX_EMAIL_LEN];
    char password[50];
} User;

User loggedInUser = {"example@domain.com", "password123"}; // Example logged-in user data

int verifyPassword(const char *inputPassword) {
    return strcmp(loggedInUser.password, inputPassword) == 0;
}

int isEmailValid(const char *email) {
    const char *atPos = strchr(email, '@');
    if (!atPos || atPos == email) {
        return 0; // No '@' or starts with '@'
    }

    const char *dotPos = strrchr(atPos, '.');
    if (!dotPos || dotPos == atPos) {
        return 0; // No '.' after '@' or immediately follows '@'
    }
    return 1;
}

void changeEmail(char *oldEmail, char *newEmail, char *confirmPassword) {
    if (strcmp(loggedInUser.currentEmail, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (!verifyPassword(confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    if (!isEmailValid(newEmail)) {
        printf("New email is invalid.\n");
        return;
    }

    strcpy(loggedInUser.currentEmail, newEmail);
    printf("Email changed successfully to %s\n", loggedInUser.currentEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[50];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);
    
    return 0;
}