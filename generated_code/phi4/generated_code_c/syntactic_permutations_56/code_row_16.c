#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticate(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (strcmp(old_email, user->email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }
    if (strcmp(user->password, confirm_password) != 0) {
        printf("Password incorrect.\n");
        return;
    }
    if (strcmp(new_email, user->email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }
    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User currentUser = {"user@example.com", "password123"};
    
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    printf("Enter your email: ");
    fgets(old_email, MAX_EMAIL_LEN, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (!authenticate(&currentUser, old_email, password)) {
        printf("Authentication failed.\n");
        return 1;
    }

    printf("Enter new email: ");
    fgets(new_email, MAX_EMAIL_LEN, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    printf("Confirm your password to change email: ");
    fgets(confirm_password, MAX_PASSWORD_LEN, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';

    changeEmail(&currentUser, old_email, new_email, confirm_password);

    return 0;
}