#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char currentEmail[MAX_EMAIL_LENGTH];
} User;

void loginUser(User *user) {
    printf("Enter your email: ");
    fgets(user->currentEmail, MAX_EMAIL_LENGTH, stdin);
    // Remove newline character if present
    user->currentEmail[strcspn(user->currentEmail, "\n")] = '\0';
}

int verifyPassword(const char *password, const char *confirmPassword) {
    return strcmp(password, confirmPassword) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    if (strcmp(user->currentEmail, oldEmail) != 0) {
        printf("Old email does not match the logged in user.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(password, MAX_EMAIL_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_EMAIL_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (!verifyPassword(password, confirmPassword)) {
        printf("Passwords do not match.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    strcpy(user->currentEmail, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user;
    
    loginUser(&user);

    changeEmail(&user);

    return 0;
}