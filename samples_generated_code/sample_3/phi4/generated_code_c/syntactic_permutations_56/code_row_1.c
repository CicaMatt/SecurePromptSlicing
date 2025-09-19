#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char currentEmail[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int verifyLogin(User user, const char* enteredPassword) {
    return strcmp(user.password, enteredPassword) == 0;
}

int changeEmail(User *user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (strcmp(user->currentEmail, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return 0;
    }
    
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 0;
    }
    
    strcpy(user->currentEmail, newEmail);
    printf("Email changed successfully!\n");
    return 1;
}

int main() {
    User user = {"user@example.com", "password123"};

    char enteredPassword[MAX_PASSWORD_LEN];
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter password to log in: ");
    scanf("%s", enteredPassword);

    if (!verifyLogin(user, enteredPassword)) {
        printf("Incorrect login credentials.\n");
        return 1;
    }

    printf("Current email: %s\n", user.currentEmail);
    printf("Enter old email: ");
    scanf("%s", oldEmail);
    printf("Enter new email: ");
    scanf("%s", newEmail);
    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}