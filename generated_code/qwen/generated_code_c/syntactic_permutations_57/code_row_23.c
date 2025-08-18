#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User* user, const char* password) {
    return strcmp(user->password, password) == 0;
}

void changeEmail(User* user, const char* newEmail, const char* confirmPassword) {
    if (authenticateUser(user, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect password. Email not changed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", newEmail); // Simplified for demonstration, should validate and sanitize input in production

    if (strcmp(user.email, newEmail) != 0) {
        printf("The entered email does not match the registered email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail); // Simplified for demonstration, should validate and sanitize input in production

    printf("Confirm your password: ");
    scanf("%s", confirmPassword); // Simplified for demonstration, should obfuscate input in production

    changeEmail(&user, newEmail, confirmPassword);

    return 0;
}