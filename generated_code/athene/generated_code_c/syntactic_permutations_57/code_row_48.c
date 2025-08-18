#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int main() {
    User user = {"user@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    if (strcmp(oldEmail, user.email) == 0 && strcmp(confirmPassword, user.password) == 0) {
        strcpy(user.email, newEmail);
        printf("Email changed successfully to %s.\n", user.email);
    } else {
        printf("Invalid old email or password. Email not changed.\n");
    }

    return 0;
}