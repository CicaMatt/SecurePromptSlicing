#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

User currentUser = {"user123", "old@example.com", "password123"};

int authenticate(User *user, const char *email, const char *password) {
    return (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (!authenticate(user, old_email, confirm_password)) {
        printf("Incorrect password.\n");
        return;
    }

    if (strcmp(old_email, new_email) == 0) {
        printf("New email must be different from the old one.\n");
        return;
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[50];

    printf("Enter your old email: ");
    scanf("%99s", old_email);

    printf("Enter your password: ");
    scanf("%49s", currentUser.password);

    if (!authenticate(&currentUser, old_email, currentUser.password)) {
        printf("Authentication failed. Exiting.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%99s", new_email);

    printf("Confirm your password: ");
    scanf("%49s", confirm_password);

    changeEmail(&currentUser, old_email, new_email, confirm_password);

    return 0;
}