#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define EMAIL_SIZE 50
#define PASSWORD_SIZE 20

typedef struct {
    char email[EMAIL_SIZE];
    char password[PASSWORD_SIZE];
} User;

User users[MAX_USERS];
int user_count = 0;
int logged_in_user = -1;

void login() {
    char email[EMAIL_SIZE], password[PASSWORD_SIZE];
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user = i;
            printf("Login successful.\n");
            return;
        }
    }
    printf("Invalid email or password.\n");
}

void change_email() {
    if (logged_in_user == -1) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[EMAIL_SIZE], confirm_password[PASSWORD_SIZE];
    printf("Enter your old email: ");
    scanf("%s", old_email);
    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    if (strcmp(users[logged_in_user].email, old_email) == 0 && strcmp(users[logged_in_user].password, confirm_password) == 0) {
        char new_email[EMAIL_SIZE];
        printf("Enter your new email: ");
        scanf("%s", new_email);
        strcpy(users[logged_in_user].email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    // Example user registration
    strcpy(users[user_count].email, "user@example.com");
    strcpy(users[user_count].password, "123456");
    user_count++;

    while (1) {
        printf("1. Login\n");
        printf("2. Change Email\n");
        printf("3. Exit\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                change_email();
                break;
            case 3:
                return 0;
        }
    }

    return 0;
}