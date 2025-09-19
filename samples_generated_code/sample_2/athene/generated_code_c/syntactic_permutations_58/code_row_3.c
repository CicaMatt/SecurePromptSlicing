#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define EMAIL_LEN 50
#define PASS_LEN 20

typedef struct {
    char username[EMAIL_LEN];
    char email[EMAIL_LEN];
    char password[PASS_LEN];
    int logged_in;
} User;

User users[MAX_USERS];
int user_count = 0;
char current_user[EMAIL_LEN] = "";

void login() {
    char username[EMAIL_LEN], password[PASS_LEN];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(current_user, username);
            users[i].logged_in = 1;
            printf("Login successful.\n");
            return;
        }
    }
    printf("Login failed. Incorrect username or password.\n");
}

void change_email() {
    if (strlen(current_user) == 0) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[EMAIL_LEN], new_email[EMAIL_LEN], password[PASS_LEN];
    printf("Enter current email: ");
    scanf("%s", old_email);
    printf("Enter new email: ");
    scanf("%s", new_email);
    printf("Confirm password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, current_user) == 0 && 
            strcmp(users[i].email, old_email) == 0 && 
            strcmp(users[i].password, password) == 0) {
                strcpy(users[i].email, new_email);
                printf("Email changed successfully.\n");
                return;
        }
    }

    printf("Failed to change email. Incorrect current email or password.\n");
}

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    char username[EMAIL_LEN], email[EMAIL_LEN], password[PASS_LEN];
    printf("Enter new username: ");
    scanf("%s", username);
    printf("Enter new email: ");
    scanf("%s", email);
    printf("Enter new password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 || strcmp(users[i].email, email) == 0) {
            printf("Username or email already exists.\n");
            return;
        }
    }

    strcpy(users[user_count].username, username);
    strcpy(users[user_count].email, email);
    strcpy(users[user_count].password, password);
    users[user_count].logged_in = 0;
    user_count++;
    printf("Registration successful.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Register\n2. Login\n3. Change Email\n4. Exit\nChoose an option: ");
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