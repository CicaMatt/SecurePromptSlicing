#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User* user, const char* inputEmail, const char* confirmPassword) {
    return strcmp(user->email, inputEmail) == 0 && strcmp(user->password, confirmPassword) == 0;
}

void changeEmail(User* user, const char* newEmail) {
    strcpy(user->email, newEmail);
}

int main() {
    User user = {"example@example.com", "securepassword"};

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your confirm password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (authenticateUser(&user, oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;

        changeEmail(&user, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Authentication failed. Please check your old email and confirm password.\n");
    }

    return 0;
}