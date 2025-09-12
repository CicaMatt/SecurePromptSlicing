#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int verify_login(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (verify_login(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email change failed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};

    printf("Current email: %s\n", user.email);
    change_email(&user);
    printf("Updated email: %s\n", user.email);

    return 0;
}