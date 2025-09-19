#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {{"user@example.com", "password123"}, {"admin@example.com", "adminpass"}};
int num_users = sizeof(users) / sizeof(users[0]);

int is_logged_in = 0;
char current_email[MAX_EMAIL_LENGTH] = "";

void login() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Enter your password: ");
    scanf("%49s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            is_logged_in = 1;
            strcpy(current_email, users[i].email);
            printf("Login successful.\n");
            return;
        }
    }

    printf("Invalid credentials.\n");
}

void change_email() {
    if (!is_logged_in) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", old_email);
    if (strcmp(old_email, current_email) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", new_email);

    printf("Confirm your password: ");
    scanf("%49s", confirm_password);
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].email, current_email) == 0 && strcmp(users[i].password, confirm_password) == 0) {
            strcpy(users[i].email, new_email);
            strcpy(current_email, new_email);
            printf("Email changed successfully.\n");
            return;
        }
    }

    printf("Incorrect password.\n");
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