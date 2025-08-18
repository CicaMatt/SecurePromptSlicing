#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

int isLoggedIn(User *user) {
    return user->username[0] != '\0' && user->email[0] != '\0';
}

int verifyPassword(const User *user, const char *password) {
    return strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (strcmp(user->email, old_email) != 0) {
        printf("Old email does not match.\n");
        return;
    }
    if (!verifyPassword(user, confirm_password)) {
        printf("Incorrect password.\n");
        return;
    }
    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User currentUser = {"john_doe", "john@example.com", "securepassword"};

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[50];

    if (!isLoggedIn(&currentUser)) {
        printf("User must be logged in to change email.\n");
        return 1;
    }

    printf("Enter your current email: ");
    scanf("%s", old_email);
    printf("Enter your new email: ");
    scanf("%s", new_email);
    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    changeEmail(&currentUser, old_email, new_email, confirm_password);

    return 0;
}