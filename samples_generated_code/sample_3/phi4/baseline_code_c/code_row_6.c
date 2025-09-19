#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100

typedef struct {
    char current_email[MAX_EMAIL_LEN];
    char password[20];
} User;

int authenticate(User *user, const char *email, const char *password) {
    return strcmp(user->current_email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (authenticate(user, old_email, confirm_password)) {
        strncpy(user->current_email, new_email, MAX_EMAIL_LEN - 1);
        user->current_email[MAX_EMAIL_LEN - 1] = '\0'; // Ensure null-termination
        printf("Email changed successfully to %s\n", new_email);
    } else {
        printf("Authentication failed. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};

    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[20];

    printf("Please enter your old email: ");
    fgets(old_email, MAX_EMAIL_LEN, stdin);
    old_email[strcspn(old_email, "\n")] = '\0'; // Remove newline character

    printf("Please enter your new email: ");
    fgets(new_email, MAX_EMAIL_LEN, stdin);
    new_email[strcspn(new_email, "\n")] = '\0'; // Remove newline character

    printf("Please confirm your password: ");
    fgets(confirm_password, 20, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0'; // Remove newline character

    changeEmail(&user, old_email, new_email, confirm_password);

    return 0;
}