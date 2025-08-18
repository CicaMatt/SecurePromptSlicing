#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define EMAIL_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 20

typedef struct {
    char username[EMAIL_MAX_LENGTH];
    char email[EMAIL_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;
char current_username[EMAIL_MAX_LENGTH] = "";

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(current_username, username);
            printf("Login successful.\n");
            return;
        }
    }
    printf("Invalid username or password.\n");
}

int change_email(const char *old_email, const char *new_email, const char *password) {
    if (strlen(current_username) == 0) {
        printf("You must be logged in to change email.\n");
        return 0;
    }

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_username) == 0 && strcmp(users[i].password, password) == 0) {
            if (strcmp(users[i].email, old_email) != 0) {
                printf("Old email does not match.\n");
                return 0;
            }
            if (strcmp(old_email, new_email) == 0) {
                printf("New email must be different from the old email.\n");
                return 0;
            }
            strcpy(users[i].email, new_email);
            printf("Email changed successfully.\n");
            return 1;
        }
    }
    printf("Incorrect password.\n");
    return 0;
}

void register_user(const char *username, const char *email, const char *password) {
    if (user_count < MAX_USERS) {
        strcpy(users[user_count].username, username);
        strcpy(users[user_count].email, email);
        strcpy(users[user_count].password, password);
        user_count++;
        printf("User registered successfully.\n");
    } else {
        printf("Maximum number of users reached.\n");
    }
}

int main() {
    register_user("user1", "user1@example.com", "pass123");
    login("user1", "pass123");

    char old_email[EMAIL_MAX_LENGTH];
    char new_email[EMAIL_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", old_email);
    printf("Enter your new email: ");
    scanf("%s", new_email);
    printf("Confirm your password: ");
    scanf("%s", password);

    change_email(old_email, new_email, password);

    return 0;
}