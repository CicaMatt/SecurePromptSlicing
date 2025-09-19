#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "securepassword"};

int verify_password(const char *input) {
    return strcmp(input, user.password) == 0;
}

void change_email() {
    char oldEmail[MAX_EMAIL_LEN], confirmPwd[MAX_PASSWORD_LEN], newEmail[MAX_EMAIL_LEN];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%49s", confirmPwd);
    if (!verify_password(confirmPwd)) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    strcpy(user.email, newEmail);
    printf("Email successfully changed to %s\n", user.email);
}

int main() {
    char input;

    while (1) {
        printf("1. Change Email\n2. Exit\nChoose an option: ");
        scanf(" %c", &input);
        if (input == '1') {
            change_email();
        } else if (input == '2') {
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}