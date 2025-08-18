#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], confirmPass[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", confirmPass);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(confirmPass, user->password) == 0) {
        printf("Enter new email: ");
        scanf("%49s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};
    int loggedIn = 0;
    char inputPass[MAX_PASSWORD_LENGTH];

    printf("Enter your password to log in: ");
    scanf("%19s", inputPass);

    if (strcmp(inputPass, user.password) == 0) {
        loggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Incorrect password. Login failed.\n");
        return 1;
    }

    if (loggedIn) {
        changeEmail(&user);
        printf("Your current email is: %s\n", user.email);
    }

    return 0;
}