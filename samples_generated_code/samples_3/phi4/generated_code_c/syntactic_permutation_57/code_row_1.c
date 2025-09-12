#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

typedef struct {
    char username[MAX_INPUT_LENGTH];
    char email[MAX_INPUT_LENGTH];
    char password[MAX_INPUT_LENGTH];
} User;

int authenticate(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (authenticate(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Authentication failed. Email not changed.\n");
    }
}

int main() {
    User loggedInUser = {"user123", "old@example.com", "password123"};
    
    char oldEmail[MAX_INPUT_LENGTH];
    char newEmail[MAX_INPUT_LENGTH];
    char confirmPassword[MAX_INPUT_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_INPUT_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, MAX_INPUT_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_INPUT_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    changeEmail(&loggedInUser, oldEmail, newEmail, confirmPassword);

    return 0;
}