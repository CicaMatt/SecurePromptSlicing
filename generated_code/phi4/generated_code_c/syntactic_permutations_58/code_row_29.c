#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char entered_password[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0'; // Remove newline character

    if (strcmp(old_email, user->email) != 0) {
        printf("Incorrect old email. Email not changed.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(entered_password, MAX_PASSWORD_LENGTH, stdin);
    entered_password[strcspn(entered_password, "\n")] = '\0'; // Remove newline character

    if (strcmp(entered_password, user->password) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = '\0'; // Remove newline character

    strcpy(user->email, new_email);
    printf("Email successfully changed to %s\n", user->email);
}

int main() {
    User user = {"JohnDoe", "john@example.com", "password123"};

    char login_password[MAX_PASSWORD_LENGTH];
    printf("Enter your password to log in: ");
    fgets(login_password, MAX_PASSWORD_LENGTH, stdin);
    login_password[strcspn(login_password, "\n")] = '\0'; // Remove newline character

    if (strcmp(login_password, user.password) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 1;
    }

    printf("You are logged in as %s\n", user.username);
    changeEmail(&user);

    return 0;
}