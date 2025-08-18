#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

void changeEmail(User *user) {
    char currentEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];

    printf("Enter your current email: ");
    scanf("%s", currentEmail);
    if (strcmp(currentEmail, user->email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    strcpy(user->email, newEmail);
    printf("Your email has been changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    char loginEmail[MAX_EMAIL];
    char loginPassword[MAX_PASSWORD];

    printf("Enter your email to log in: ");
    scanf("%s", loginEmail);
    printf("Enter your password to log in: ");
    scanf("%s", loginPassword);

    if (strcmp(loginEmail, user.email) == 0 && strcmp(loginPassword, user.password) == 0) {
        printf("Login successful.\n");
        changeEmail(&user);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}