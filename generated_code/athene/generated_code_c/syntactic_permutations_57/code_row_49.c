#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[10]; // Assuming a maximum of 10 users for simplicity
int user_count = 0;
int logged_in_user = -1; // Index of the logged-in user, -1 if not logged in

void login(const char *email, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user = i;
            return;
        }
    }
}

void change_email() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    if (logged_in_user == -1) {
        printf("Please log in to change your email.\n");
        return;
    }

    printf("Enter your old email: ");
    scanf("%s", old_email);
    printf("Enter your new email: ");
    scanf("%s", new_email);
    printf("Confirm password: ");
    scanf("%s", confirm_password);

    if (strcmp(old_email, users[logged_in_user].email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (strcmp(confirm_password, users[logged_in_user].password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(users[logged_in_user].email, new_email);
    printf("Email changed successfully.\n");
}

int main() {
    // Example user creation
    strcpy(users[user_count++].email, "user@example.com");
    strcpy(users[user_count++].password, "password123");

    char choice;
    while (1) {
        printf("1. Login\n2. Change Email\n3. Exit\n");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': {
                char email[MAX_EMAIL_LENGTH];
                char password[MAX_PASSWORD_LENGTH];
                printf("Enter your email: ");
                scanf("%s", email);
                printf("Enter your password: ");
                scanf("%s", password);
                login(email, password);
                if (logged_in_user != -1) {
                    printf("Login successful.\n");
                } else {
                    printf("Login failed.\n");
                }
                break;
            }
            case '2':
                change_email();
                break;
            case '3':
                return 0;
        }
    }

    return 0;
}