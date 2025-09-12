#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int authenticate(User user, const char *inputEmail, const char *inputPassword) {
    return (strcmp(user.email, inputEmail) == 0 &&
            strcmp(user.password, inputPassword) == 0);
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword, const char *password) {
    if (!authenticate(*user, oldEmail, password)) {
        printf("Authentication failed. Incorrect email or password.\n");
        return;
    }
    
    if (strcmp(user->email, newEmail) == 0) {
        printf("New email must be different from the current email.\n");
        return;
    }

    int confirmPassValid = strcmp(confirmPassword, password) == 0;
    if (!confirmPassValid) {
        printf("Passwords do not match. Try again.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User currentUser = {"user@example.com", "password123"};
    
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_EMAIL_LENGTH];
    char confirmNewPassword[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(inputPassword, MAX_EMAIL_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';
    
    printf("Confirm your password for verification: ");
    fgets(confirmNewPassword, MAX_EMAIL_LENGTH, stdin);
    confirmNewPassword[strcspn(confirmNewPassword, "\n")] = '\0';

    changeEmail(&currentUser, oldEmail, newEmail, confirmNewPassword, inputPassword);

    return 0;
}