#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL], confirmPass[MAX_PASSWORD], newEmail[MAX_EMAIL];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPass);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(confirmPass, user->password) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    int loggedIn = 0;

    char inputPass[MAX_PASSWORD];
    printf("Enter your password to log in: ");
    scanf("%s", inputPass);

    if (strcmp(inputPass, user.password) == 0) {
        loggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Incorrect password. Login failed.\n");
    }

    if (loggedIn) {
        changeEmail(&user);
    }

    return 0;
}