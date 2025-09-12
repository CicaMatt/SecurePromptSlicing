#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20]; // Simple representation of a password
} User;

int authenticate_user(User *user, const char* old_email, const char* confirm_password) {
    if (strcmp(user->email, old_email) != 0 || strcmp(user->password, confirm_password) != 0) {
        return 0;
    }
    return 1;
}

void change_email(User *user, const char* new_email) {
    strncpy(user->email, new_email, MAX_EMAIL_LENGTH);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0'; // Ensure null-termination
}

int main() {
    User user = {"example@example.com", "password123"};
    
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[20];

    printf("Enter your old email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0'; // Remove newline character

    printf("Enter your new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirm_password, 20, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';

    if (authenticate_user(&user, old_email, confirm_password)) {
        change_email(&user, new_email);
        printf("Email changed successfully to %s\n", user.email);
    } else {
        printf("Authentication failed. Cannot change email.\n");
    }

    return 0;
}