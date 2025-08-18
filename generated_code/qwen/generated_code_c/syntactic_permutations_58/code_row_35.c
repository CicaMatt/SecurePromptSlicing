#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(User user, const char* inputEmail, const char* inputPassword) {
    return strcmp(user.email, inputEmail) == 0 && strcmp(user.password, inputPassword) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], password[MAX_PASSWORD];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your password to confirm: ");
    scanf("%s", password);

    if (authenticateUser(*user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email change failed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    char loginEmail[MAX_EMAIL], loginPassword[MAX_PASSWORD];

    printf("Login to change your email:\n");

    printf("Enter your email: ");
    scanf("%s", loginEmail);
    printf("Enter your password: ");
    scanf("%s", loginPassword);

    if (authenticateUser(user, loginEmail, loginPassword)) {
        changeEmail(&user);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}