#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user = {"JohnDoe", "john@example.com", "password123"};

    char email[MAX_EMAIL_LENGTH], password[PASSWORD_LENGTH];
    
    printf("Login\n");
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    if (login(&user, email, password)) {
        printf("Logged in successfully.\n");

        char oldEmail[MAX_EMAIL_LENGTH], newPassword[PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];
        
        printf("Enter your current email to change it: ");
        scanf("%s", oldEmail);
        printf("Confirm your password: ");
        scanf("%s", newPassword);

        printf("Enter your new email: ");
        scanf("%s", newEmail);

        change_email(&user, oldEmail, newPassword, newEmail);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}