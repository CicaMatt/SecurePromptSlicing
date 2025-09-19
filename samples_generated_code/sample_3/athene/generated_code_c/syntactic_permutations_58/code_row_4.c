#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);
    printf("Enter your password: ");
    scanf("%19s", password);

    if (authenticate(user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};

    int loggedIn = 0;
    char loginEmail[MAX_EMAIL_LENGTH], loginPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email to log in: ");
    scanf("%49s", loginEmail);
    printf("Enter your password to log in: ");
    scanf("%19s", loginPassword);

    if (authenticate(&user, loginEmail, loginPassword)) {
        loggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
        return 1;
    }

    if (loggedIn) {
        changeEmail(&user);
    }

    return 0;
}