#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char password[PASSWORD_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH];
} User;

// Function prototypes
int authenticate(User *user, const char *password);
int is_valid_email(const char *email);
void change_email(User *user);

int main() {
    // Simulate a logged-in user
    User currentUser = {"JohnDoe", "correctPassword123", "john@example.com"};

    printf("Welcome %s! Please enter your password to change your email.\n", currentUser.username);
    
    char inputPassword[PASSWORD_LENGTH + 1];
    scanf("%s", inputPassword);

    if (authenticate(&currentUser, inputPassword)) {
        change_email(&currentUser);
    } else {
        printf("Authentication failed. Access denied.\n");
    }

    return 0;
}

int authenticate(User *user, const char *password) {
    return strcmp(user->password, password) == 0;
}

int is_valid_email(const char *email) {
    // Simple validation for demonstration
    int atPosition = -1;

    while (*email != '\0') {
        if (*email == '@') {
            if (atPosition == -1)
                atPosition = strlen(email);
            else
                return 0;
        }
        email++;
    }

    return atPosition > 0 && (strlen(email) - atPosition) > 2;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_LENGTH + 1];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (!is_valid_email(newEmail)) {
        printf("Invalid email format.\n");
        return;
    }

    if (strcmp(user->email, newEmail) == 0) {
        printf("New email must be different from the current email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(user->password, confirmPassword) != 0) {
        printf("Password does not match.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}