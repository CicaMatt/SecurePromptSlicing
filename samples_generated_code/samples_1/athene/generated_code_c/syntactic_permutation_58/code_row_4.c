#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN], newEmail[MAX_EMAIL_LEN];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);
    printf("Enter your password: ");
    scanf("%19s", confirmPassword);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(confirmPassword, user->password) == 0) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};

    changeEmail(&user);

    printf("Current email: %s\n", user.email);

    return 0;
}