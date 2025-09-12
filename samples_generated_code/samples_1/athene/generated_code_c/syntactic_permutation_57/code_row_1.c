#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {{"user@example.com", "password123"}, {"admin@example.com", "adminpass"}};
int user_count = sizeof(users) / sizeof(users[0]);
int logged_in_user = -1;

void login() {
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Enter your password: ");
    scanf("%49s", password);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user = i;
            printf("Login successful!\n");
            return;
        }
    }
    printf("Invalid credentials.\n");
}

void change_email() {
    if (logged_in_user == -1) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], confirm_password[MAX_PASSWORD_LEN];
    printf("Enter your current email: ");
    scanf("%99s", old_email);
    printf("Enter your new email: ");
    scanf("%99s", new_email);
    printf("Confirm your password: ");
    scanf("%49s", confirm_password);

    if (strcmp(old_email, users[logged_in_user].email) == 0 && strcmp(confirm_password, users[logged_in_user].password) == 0) {
        strcpy(users[logged_in_user].email, new_email);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
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
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}