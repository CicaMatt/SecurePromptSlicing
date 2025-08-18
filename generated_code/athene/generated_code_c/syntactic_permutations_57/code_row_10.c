#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};

int main() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);
    if (strcmp(confirmPassword, user.password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(user.email, newEmail);
    printf("Your email has been successfully changed to %s\n", user.email);

    return 0;
}