#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect email. Email change failed.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    scanf("%s", password);

    if (strcmp(password, user->password) != 0) {
        printf("Incorrect password. Email change failed.\n");
        return;
    }

    printf("Enter the new email: ");
    scanf("%s", newEmail);

    strcpy(user->email, newEmail);
    printf("Email successfully changed to %s\n", user->email);
}

int main() {
    User user = {"user@example.com", "password123"};
    char loginPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your password to log in: ");
    scanf("%s", loginPassword);

    if (strcmp(loginPassword, user.password) != 0) {
        printf("Login failed. Incorrect password.\n");
        return 1;
    }

    printf("Logged in successfully.\n");

    changeEmail(&user);

    return 0;
}