#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User currentUser;

int isLoggedIn() {
    return strcmp(currentUser.username, "") != 0;
}

int verifyPassword(const char *inputPassword) {
    return strcmp(currentUser.password, inputPassword) == 0;
}

int isEmailValid(const char *email) {
    // Very basic email validation
    int atPos = -1;
    for (int i = 0; email[i] != '\0'; ++i) {
        if (email[i] == '@') {
            if (atPos == -1) atPos = i;
            else return 0; // More than one '@'
        }
    }
    return atPos > 0 && atPos < strlen(email) - 1;
}

void changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!isLoggedIn()) {
        printf("User must be logged in to change email.\n");
        return;
    }
    
    if (strcmp(currentUser.email, oldEmail) != 0) {
        printf("Old email does not match the current account's email.\n");
        return;
    }

    if (!verifyPassword(confirmPassword)) {
        printf("Invalid password.\n");
        return;
    }

    if (!isEmailValid(newEmail)) {
        printf("New email is not valid.\n");
        return;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    // Simulating a logged-in user
    strcpy(currentUser.username, "john_doe");
    strcpy(currentUser.email, "old_email@example.com");
    strcpy(currentUser.password, "securepassword123");

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH];

    printf("Current Email: %s\n", currentUser.email);
    
    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm Password: ");
    scanf("%19s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}