#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LEN];
} User;

User loggedInUser = {"existing@example.com", "password123"};

int verifyPassword(const char *input, const char *correct) {
    return strcmp(input, correct) == 0;
}

int changeEmail(char oldEmail[], char newEmail[], char confirmPassword[]) {
    if (strcmp(loggedInUser.email, oldEmail) != 0) {
        printf("Old email does not match the current logged-in email.\n");
        return -1;
    }

    if (!verifyPassword(confirmPassword, loggedInUser.password)) {
        printf("Incorrect password.\n");
        return -2;
    }
    
    // Simulate email existence check; assuming all emails are valid in this context
    if (strlen(newEmail) == 0) {
        printf("New email is invalid.\n");
        return -3;
    }

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully to %s\n", loggedInUser.email);
    return 0;
}

int main() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[PASSWORD_LEN];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}