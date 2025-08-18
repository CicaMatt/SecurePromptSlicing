#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[100]; // Assume we have a fixed array of users for simplicity
int user_count = 0;
int current_user_id = -1; // -1 means no one is logged in

void login(const char *email, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            current_user_id = i;
            return;
        }
    }
}

int change_email(const char *old_email, const char *new_email, const char *confirm_password) {
    if (current_user_id == -1) {
        return 0; // Not logged in
    }

    User *user = &users[current_user_id];
    if (strcmp(user->email, old_email) != 0 || strcmp(user->password, confirm_password) != 0) {
        return 0; // Incorrect email or password
    }

    strncpy(user->email, new_email, MAX_EMAIL_LENGTH - 1);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0';
    return 1; // Success
}

int main() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    // Example: Register a user for testing
    User test_user = {"example@example.com", "password"};
    users[user_count++] = test_user;

    // Simulate login
    login("example@example.com", "password");

    if (current_user_id == -1) {
        printf("Login failed.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%49s", old_email);
    printf("Enter new email: ");
    scanf("%49s", new_email);
    printf("Confirm password: ");
    scanf("%19s", confirm_password);

    if (change_email(old_email, new_email, confirm_password)) {
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Please check your inputs and try again.\n");
    }

    return 0;
}