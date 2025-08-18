#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User loggedInUser = {"user@example.com", "password123"};

int authenticate(const char *email, const char *confirmPassword) {
    return strcmp(loggedInUser.email, email) == 0 && strcmp(loggedInUser.password, confirmPassword) == 0;
}

int changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (authenticate(oldEmail, confirmPassword)) {
        strncpy(loggedInUser.email, newEmail, MAX_EMAIL_LENGTH);
        loggedInUser.email[MAX_EMAIL_LENGTH - 1] = '\0';
        return 1;
    }
    return 0;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Enter confirm password: ");
    fgets(confirmPassword, PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (changeEmail(oldEmail, newEmail, confirmPassword)) {
        printf("Email successfully changed to %s\n", loggedInUser.email);
    } else {
        printf("Failed to change email. Please check your credentials.\n");
    }

    return 0;
}