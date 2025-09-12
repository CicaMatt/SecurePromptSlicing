#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

int authenticate(User *user, const char *email, const char *password) {
    return (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (authenticate(user, old_email, confirm_password)) {
        strncpy(user->email, new_email, MAX_EMAIL_LENGTH - 1);
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Email not changed.\n");
    }
}

int main() {
    User user = {"JohnDoe", "john@example.com", "password123"};

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[50];

    printf("Enter your current email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirm_password, 50, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';

    changeEmail(&user, old_email, new_email, confirm_password);

    return 0;
}