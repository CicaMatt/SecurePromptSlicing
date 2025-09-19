#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int login(const char *username, const char *password) {
    // Dummy user credentials for demonstration
    const char *correct_username = "user";
    const char *correct_password = "pass";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

int change_email(const char *old_email, const char *new_email, const char *password) {
    if (login("user", password)) {
        if (strcmp(old_email, new_email) != 0) {
            // Dummy check for email validity
            if (strchr(new_email, '@') && strchr(new_email, '.')) {
                printf("Email changed successfully.\n");
                return 1;
            } else {
                printf("Invalid new email format.\n");
                return 0;
            }
        } else {
            printf("New email must be different from old email.\n");
            return 0;
        }
    } else {
        printf("Incorrect password.\n");
        return 0;
    }
}

int main() {
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%19s", password);

    if (login(username, password)) {
        printf("Login successful.\n");
        printf("Enter old email: ");
        scanf("%49s", old_email);
        printf("Enter new email: ");
        scanf("%49s", new_email);
        printf("Confirm password: ");
        scanf("%19s", password);

        change_email(old_email, new_email, password);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}