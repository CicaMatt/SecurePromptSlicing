#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define EMAIL_LEN 50
#define PASSWORD_LEN 20

typedef struct {
    char email[EMAIL_LEN];
    char password[PASSWORD_LEN];
} User;

User users[MAX_USERS];
int user_count = 0;
char current_user_email[EMAIL_LEN] = "";

void login(char *email, char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(current_user_email, email);
            return;
        }
    }
    printf("Invalid credentials.\n");
}

int is_logged_in() {
    return strlen(current_user_email) > 0;
}

void change_email(char *old_email, char *new_email, char *confirm_password) {
    if (!is_logged_in()) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, old_email) == 0 && strcmp(users[i].password, confirm_password) == 0) {
            strcpy(users[i].email, new_email);
            printf("Email changed successfully.\n");
            return;
        }
    }

    printf("Incorrect information provided.\n");
}

int main() {
    // Example users
    strcpy(users[0].email, "user1@example.com");
    strcpy(users[0].password, "password1");
    user_count++;

    // Login
    char email[EMAIL_LEN], password[PASSWORD_LEN];
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    login(email, password);

    if (is_logged_in()) {
        printf("Logged in as %s\n", current_user_email);

        // Change email
        char old_email[EMAIL_LEN], new_email[EMAIL_LEN], confirm_password[PASSWORD_LEN];
        printf("Enter your old email: ");
        scanf("%s", old_email);
        printf("Enter your new email: ");
        scanf("%s", new_email);
        printf("Confirm your password: ");
        scanf("%s", confirm_password);

        change_email(old_email, new_email, confirm_password);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}