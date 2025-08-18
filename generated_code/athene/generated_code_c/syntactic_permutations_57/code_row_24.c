#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int is_logged_in = 0; // Assume the user needs to log in first

void login(const char* email, const char* password) {
    if (strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0) {
        is_logged_in = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }
}

void change_email(const char* new_email, const char* confirm_password) {
    if (!is_logged_in) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(confirm_password, user.password) != 0) {
        printf("Incorrect password. Cannot change email.\n");
        return;
    }

    strcpy(user.email, new_email);
    printf("Email changed successfully to: %s\n", user.email);
}

int main() {
    char current_email[MAX_EMAIL_LENGTH];
    char current_password[MAX_PASSWORD_LENGTH];

    printf("Enter your email to log in: ");
    scanf("%49s", current_email);

    printf("Enter your password to log in: ");
    scanf("%19s", current_password);

    login(current_email, current_password);

    if (is_logged_in) {
        char new_email[MAX_EMAIL_LENGTH];
        char confirm_password[MAX_PASSWORD_LENGTH];

        printf("Enter new email: ");
        scanf("%49s", new_email);

        printf("Confirm password to change email: ");
        scanf("%19s", confirm_password);

        change_email(new_email, confirm_password);
    }

    return 0;
}