#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20];
} User;

int authenticate(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
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
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"user@example.com", "password123"};

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[20];

    printf("Enter your old email: ");
    scanf("%99s", old_email);

    printf("Enter your password to confirm: ");
    scanf("%19s", confirm_password);

    if (!authenticate(&user, old_email, confirm_password)) {
        printf("Authentication failed.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%99s", new_email);
    
    changeEmail(&user, old_email, new_email, confirm_password);

    return 0;
}