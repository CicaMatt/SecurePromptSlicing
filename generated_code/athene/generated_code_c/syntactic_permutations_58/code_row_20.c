#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int logged_in;
} User;

User users[MAX_USERS];
int user_count = 0;
int current_user_id = -1;

void login() {
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            users[i].logged_in = 1;
            current_user_id = i;
            printf("Login successful.\n");
            return;
        }
    }
    printf("Invalid email or password.\n");
}

void change_email() {
    if (current_user_id == -1) {
        printf("You must log in first.\n");
        return;
    }

    char old_email[MAX_EMAIL_LENGTH], confirm_password[MAX_PASSWORD_LENGTH];
    printf("Enter your old email: ");
    scanf("%s", old_email);
    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    if (strcmp(users[current_user_id].email, old_email) == 0 && strcmp(users[current_user_id].password, confirm_password) == 0) {
        char new_email[MAX_EMAIL_LENGTH];
        printf("Enter your new email: ");
        scanf("%s", new_email);
        strcpy(users[current_user_id].email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    User new_user;
    printf("Enter your email: ");
    scanf("%s", new_user.email);
    printf("Enter your password: ");
    scanf("%s", new_user.password);
    new_user.logged_in = 0;

    users[user_count++] = new_user;
    printf("User registered successfully.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Register\n2. Login\n3. Change Email\n4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                login();
                break;
            case 3:
                change_email();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}