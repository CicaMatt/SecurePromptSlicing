#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User loggedInUser;

bool authenticate(User user, const char* enteredPassword) {
    return strcmp(user.password, enteredPassword) == 0;
}

bool changeEmail(User *user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return false;
    }
    
    if (strcmp(newEmail, user->email) == 0) {
        printf("New email must be different from the current email.\n");
        return false;
    }

    if (strlen(confirmPassword) != strlen(user->password)) {
        printf("Passwords do not match in length.\n");
        return false;
    }
    
    for (int i = 0; confirmPassword[i] != '\0'; ++i) {
        if (confirmPassword[i] != user->password[i]) {
            printf("Passwords do not match.\n");
            return false;
        }
    }

    strcpy(user->email, newEmail);
    printf("Email successfully changed to %s\n", newEmail);
    return true;
}

int main() {
    // Simulate a logged in user
    strcpy(loggedInUser.username, "john_doe");
    strcpy(loggedInUser.email, "old_email@example.com");
    strcpy(loggedInUser.password, "securepassword");

    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char enteredPassword[MAX_PASSWORD_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';  // Remove newline character

    printf("Enter your password to confirm identity: ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0';

    if (!authenticate(loggedInUser, enteredPassword)) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password to change the email: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (!changeEmail(&loggedInUser, oldEmail, newEmail, confirmPassword)) {
        return 1;
    }

    return 0;
}