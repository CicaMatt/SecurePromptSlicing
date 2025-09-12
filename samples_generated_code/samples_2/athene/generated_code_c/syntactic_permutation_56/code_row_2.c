#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"john_doe", "john@example.com", "password123"};

int validate_password(const char *input) {
    return strcmp(input, user.password) == 0;
}

void change_email() {
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", old_email);
    if (strcmp(old_email, user.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", new_email);

    printf("Confirm password to change email: ");
    scanf("%s", password);

    if (!validate_password(password)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user.email, new_email);
    printf("Email successfully changed to %s\n", user.email);
}

int main() {
    int logged_in = 1; // Assume the user is already logged in for simplicity

    if (!logged_in) {
        printf("You must be logged in to change your email.\n");
        return 1;
    }

    change_email();

    return 0;
}