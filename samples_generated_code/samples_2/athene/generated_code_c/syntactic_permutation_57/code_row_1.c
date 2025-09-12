#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {{"user@example.com", "password123"}, {"admin@example.com", "adminpass"}};
int num_users = sizeof(users) / sizeof(users[0]);

int is_logged_in = 0;
char logged_in_email[MAX_EMAIL_LEN] = "";

void login(const char *email, const char *password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            is_logged_in = 1;
            strcpy(logged_in_email, email);
            return;
        }
    }
    is_logged_in = 0;
}

int change_email(const char *old_email, const char *new_email, const char *confirm_password) {
    if (!is_logged_in) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].email, old_email) == 0 && strcmp(users[i].password, confirm_password) == 0) {
            strcpy(users[i].email, new_email);
            if (strcmp(logged_in_email, old_email) == 0) {
                strcpy(logged_in_email, new_email);
            }
            printf("Email changed successfully.\n");
            return 1;
        }
    }

    printf("Incorrect email or password.\n");
    return 0;
}

int main() {
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], confirm_password[MAX_PASSWORD_LEN];

    printf("Enter your email to log in: ");
    scanf("%99s", email);
    printf("Enter your password to log in: ");
    scanf("%49s", password);

    login(email, password);

    if (is_logged_in) {
        printf("Logged in as %s\n", logged_in_email);

        printf("Enter old email: ");
        scanf("%99s", old_email);
        printf("Enter new email: ");
        scanf("%99s", new_email);
        printf("Confirm password: ");
        scanf("%49s", confirm_password);

        change_email(old_email, new_email, confirm_password);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}