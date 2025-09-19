#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

User loggedInUser = {"example@example.com", "password123"}; // Example logged-in user data

int authenticate(const char* oldEmail, const char* confirmPassword) {
    return strcmp(loggedInUser.email, oldEmail) == 0 && 
           strcmp(loggedInUser.password, confirmPassword) == 0;
}

void changeEmail(const char* newEmail) {
    strncpy(loggedInUser.email, newEmail, MAX_EMAIL_LENGTH - 1);
    loggedInUser.email[MAX_EMAIL_LENGTH - 1] = '\0';
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    if (strcmp(oldEmail, loggedInUser.email) != 0) {
        printf("The provided email does not match the logged-in user.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password to verify ownership: ");
    fgets(confirmPassword, MAX_EMAIL_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (!authenticate(oldEmail, confirmPassword)) {
        printf("Authentication failed. Check the email and password.\n");
        return 1;
    }

    changeEmail(newEmail);

    printf("Your email has been successfully changed to: %s\n", loggedInUser.email);
    return 0;
}