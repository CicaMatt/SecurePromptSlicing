#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

bool checkPassword(const char *input, const char *stored) {
    return strcmp(input, stored) == 0;
}

void changeEmail(User *user) {
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%s", user->oldEmail);

    printf("Enter your current password: ");
    scanf("%s", user->password);

    if (!checkPassword(user->password, "correctPassword")) {
        printf("Incorrect password. Operation cancelled.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm new email: ");
    scanf("%s", confirmPassword);

    if (strcmp(newEmail, confirmPassword) != 0) {
        printf("New emails do not match. Operation cancelled.\n");
        return;
    }

    if (strstr(newEmail, ".") == NULL) {
        printf("New email must contain a dot ('.'). Operation cancelled.\n");
        return;
    }

    strcpy(user->oldEmail, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user;

    printf("Welcome to the login page.\n");

    changeEmail(&user);

    return 0;
}