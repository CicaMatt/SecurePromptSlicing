#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "correctPassword"

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int main() {
    User user = {"user@example.com", PASSWORD};
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%49s", oldEmail);

    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect email.\n");
        return 1;
    }

    printf("Enter your password to confirm: ");
    scanf("%25s", confirmPassword);

    if (strcmp(confirmPassword, user.password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    if (strcmp(newEmail, user.email) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    strcpy(user.email, newEmail);
    printf("Email successfully changed to %s\n", user.email);
    return 0;
}