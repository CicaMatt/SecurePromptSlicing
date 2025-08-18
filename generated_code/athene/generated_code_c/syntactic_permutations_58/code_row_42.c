#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char username[MAX_EMAIL_LEN];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int login(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    if (login(user, oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"john_doe", "john@example.com", "securepassword123"};
    int loggedIn = 0;

    char loginEmail[MAX_EMAIL_LEN], loginPassword[MAX_PASSWORD_LEN];
    printf("Login to change your email:\n");
    printf("Enter your email: ");
    scanf("%49s", loginEmail);
    printf("Enter your password: ");
    scanf("%19s", loginPassword);

    if (login(&user, loginEmail, loginPassword)) {
        loggedIn = 1;
        printf("Login successful.\n");
        change_email(&user);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}