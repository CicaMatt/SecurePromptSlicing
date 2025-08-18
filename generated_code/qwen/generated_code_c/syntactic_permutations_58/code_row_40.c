#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(User* user, const char* oldEmail, const char* password) {
    return strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User* user, const char* newEmail) {
    strcpy(user->email, newEmail);
    printf("Email successfully changed to: %s\n", user->email);
}

int main() {
    User currentUser = {"example@example.com", "securepassword123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(&currentUser, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        changeEmail(&currentUser, newEmail);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}