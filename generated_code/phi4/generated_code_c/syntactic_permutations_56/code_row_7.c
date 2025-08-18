#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100

typedef struct {
    char username[50];
    char password[50];
    char email[MAX_EMAIL_LEN];
} User;

User currentUser = {"user1", "password123", "oldemail@example.com"};

int authenticate(User *user, const char *username, const char *password) {
    return (strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (strcmp(user->email, old_email) != 0) {
        printf("Old email does not match.\n");
        return;
    }
    
    if (strcmp(user->password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    if (strcmp(old_email, new_email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully to: %s\n", user->email);
}

int main() {
    char username[50], password[50];
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], confirm_password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (!authenticate(&currentUser, username, password)) {
        printf("Authentication failed. Exiting.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%99s", old_email);

    printf("Enter new email: ");
    scanf("%99s", new_email);

    printf("Confirm password: ");
    scanf("%49s", confirm_password);

    changeEmail(&currentUser, old_email, new_email, confirm_password);

    return 0;
}