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
int logged_in_user = -1;

void login(const char *email, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            logged_in_user = i;
            return;
        }
    }
}

void logout() {
    logged_in_user = -1;
}

int change_email(const char *old_email, const char *new_email, const char *confirm_password) {
    if (logged_in_user == -1) {
        return 0; // Not logged in
    }

    User *current_user = &users[logged_in_user];
    if (strcmp(current_user->email, old_email) != 0 || strcmp(current_user->password, confirm_password) != 0) {
        return 0; // Incorrect old email or password
    }

    strcpy(current_user->email, new_email);
    return 1; // Email changed successfully
}

int main() {
    char action;
    char email[EMAIL_LEN];
    char password[PASSWORD_LEN];
    char old_email[EMAIL_LEN];
    char new_email[EMAIL_LEN];
    char confirm_password[PASSWORD_LEN];

    users[0] = (User){"user@example.com", "password123"};
    user_count++;

    while (1) {
        printf("1. Login\n2. Change Email\n3. Logout\n4. Exit\n");
        scanf(" %c", &action);

        switch(action) {
            case '1':
                printf("Enter email: ");
                scanf("%s", email);
                printf("Enter password: ");
                scanf("%s", password);
                login(email, password);
                if (logged_in_user != -1) {
                    printf("Logged in successfully.\n");
                } else {
                    printf("Login failed.\n");
                }
                break;
            case '2':
                printf("Enter old email: ");
                scanf("%s", old_email);
                printf("Enter new email: ");
                scanf("%s", new_email);
                printf("Confirm password: ");
                scanf("%s", confirm_password);
                if (change_email(old_email, new_email, confirm_password)) {
                    printf("Email changed successfully.\n");
                } else {
                    printf("Failed to change email.\n");
                }
                break;
            case '3':
                logout();
                printf("Logged out successfully.\n");
                break;
            case '4':
                return 0;
        }
    }

    return 0;
}