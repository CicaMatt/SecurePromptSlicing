#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(User user, const char* oldEmail, const char* confirmPassword) {
    return strcmp(user.email, oldEmail) == 0 && strcmp(user.password, confirmPassword) == 0;
}

void changeEmail(User *user, const char* newEmail) {
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User loggedInUser = {"example@example.com", "password123"};
    
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter the new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (authenticateUser(loggedInUser, oldEmail, confirmPassword)) {
        changeEmail(&loggedInUser, newEmail);
    } else {
        printf("Authentication failed. Please check your email and password.\n");
    }

    return 0;
}