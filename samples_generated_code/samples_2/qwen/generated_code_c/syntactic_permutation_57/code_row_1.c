#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (authenticateUser(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Please check your email and password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}