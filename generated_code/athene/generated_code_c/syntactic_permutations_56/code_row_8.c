#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

int is_logged_in = 0;
char current_email[MAX_EMAIL_LEN] = "user@example.com";
char password[MAX_PASSWORD_LEN] = "password123";

void login(const char *email, const char *pwd) {
    if (strcmp(email, current_email) == 0 && strcmp(pwd, password) == 0) {
        is_logged_in = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

void change_email() {
    if (!is_logged_in) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%49s", old_email);
    if (strcmp(old_email, current_email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%49s", new_email);
    if (strcmp(new_email, current_email) == 0) {
        printf("New email must be different from the old one.\n");
        return;
    }

    printf("Confirm password to change email: ");
    scanf("%19s", confirm_password);
    if (strcmp(confirm_password, password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(current_email, new_email);
    printf("Email changed successfully. New email is %s\n", current_email);
}

int main() {
    char email[MAX_EMAIL_LEN];
    char pwd[MAX_PASSWORD_LEN];

    printf("Enter your email: ");
    scanf("%49s", email);
    printf("Enter your password: ");
    scanf("%19s", pwd);

    login(email, pwd);

    if (is_logged_in) {
        change_email();
    }

    return 0;
}