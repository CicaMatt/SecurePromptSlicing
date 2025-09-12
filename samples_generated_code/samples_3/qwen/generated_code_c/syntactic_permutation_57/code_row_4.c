#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

bool verifyUser(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *newEmail) {
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "securepassword"};
    char currentEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(currentEmail, MAX_EMAIL_LENGTH, stdin);
    currentEmail[strcspn(currentEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (!verifyUser(&user, currentEmail, confirmPassword)) {
        printf("Invalid email or password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    changeEmail(&user, newEmail);

    return 0;
}