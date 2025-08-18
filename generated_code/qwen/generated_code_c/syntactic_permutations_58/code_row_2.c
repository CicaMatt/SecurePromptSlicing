#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User* user, const char* email, const char* password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User* user, const char* oldEmail, const char* password, const char* newEmail) {
    if (authenticateUser(user, oldEmail, password)) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
        user->email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user;
    strcpy(user.email, "example@example.com");
    strcpy(user.password, "securepassword");

    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Enter new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    changeEmail(&user, oldEmail, password, newEmail);

    return 0;
}