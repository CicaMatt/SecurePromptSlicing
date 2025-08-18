#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

typedef struct {
    char username[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
    char email[MAX_EMAIL_LEN];
} User;

int validate_password(const char *input, const char *password) {
    return strcmp(input, password) == 0;
}

int update_email(User *user) {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASS_LEN];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect old email.\n");
        return 0;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    if (strcmp(newEmail, user->email) == 0) {
        printf("New email must be different from the old email.\n");
        return 0;
    }

    printf("Confirm password to proceed: ");
    scanf("%49s", confirmPassword);
    if (!validate_password(confirmPassword, user->password)) {
        printf("Incorrect password.\n");
        return 0;
    }

    strcpy(user->email, newEmail);
    printf("Email updated successfully!\n");
    return 1;
}

int main() {
    User user = {"john_doe", "securepassword", "john@example.com"};

    char inputPassword[MAX_PASS_LEN];
    printf("Enter your password to log in: ");
    scanf("%49s", inputPassword);

    if (!validate_password(inputPassword, user.password)) {
        printf("Incorrect password. Login failed.\n");
        return 1;
    }

    printf("Logged in successfully!\n");

    update_email(&user);

    printf("Your new email is: %s\n", user.email);
    return 0;
}