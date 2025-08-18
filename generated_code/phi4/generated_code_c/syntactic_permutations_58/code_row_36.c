#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User user, const char* inputEmail, const char* inputPassword) {
    return strcmp(user.email, inputEmail) == 0 && strcmp(user.password, inputPassword) == 0;
}

int change_email(User *user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (strcmp(user->email, oldEmail) != 0 || strcmp(user->password, confirmPassword) != 0) {
        return -1; // Incorrect email or password
    }
    
    strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0'; // Ensure null termination
    return 0;
}

int main() {
    User currentUser = {"user@example.com", "password123"};
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    int loggedIn;

    printf("Enter your email: ");
    fgets(inputEmail, MAX_EMAIL_LENGTH, stdin);
    inputEmail[strcspn(inputEmail, "\n")] = '\0'; // Remove trailing newline

    printf("Enter your password: ");
    fgets(inputPassword, MAX_PASSWORD_LENGTH, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove trailing newline

    loggedIn = login(currentUser, inputEmail, inputPassword);

    if (loggedIn) {
        char oldEmail[MAX_EMAIL_LENGTH];
        char newEmail[MAX_EMAIL_LENGTH];
        char confirmPassword[MAX_PASSWORD_LENGTH];

        printf("Enter your current email: ");
        fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
        oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove trailing newline

        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove trailing newline

        printf("Confirm your password: ");
        fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove trailing newline

        int result = change_email(&currentUser, oldEmail, newEmail, confirmPassword);

        if (result == 0) {
            printf("Email successfully changed.\n");
        } else {
            printf("Failed to change email. Incorrect email or password.\n");
        }
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}