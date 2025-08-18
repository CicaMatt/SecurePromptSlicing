#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User current_user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(email, current_user.email) == 0 && strcmp(password, current_user.password) == 0) {
        return 1;
    }
    return 0;
}

void change_email() {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%99s", old_email);
    if (strcmp(old_email, current_user.email) != 0) {
        printf("Old email does not match the current user's email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", new_email);

    printf("Confirm your password to verify ownership: ");
    scanf("%49s", confirm_password);
    if (strcmp(confirm_password, current_user.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(current_user.email, new_email);
    printf("Email successfully changed to %s\n", current_user.email);
}

int main() {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Login Page:\n");
    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (login(email, password)) {
        printf("Logged in successfully.\n");
        change_email();
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}