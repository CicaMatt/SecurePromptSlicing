#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int authenticateUser(const User* user, const char* email, const char* password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User* user, const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (authenticateUser(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Enter your password to confirm: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    changeEmail(&user, oldEmail, newEmail, confirmPassword);

    return 0;
}