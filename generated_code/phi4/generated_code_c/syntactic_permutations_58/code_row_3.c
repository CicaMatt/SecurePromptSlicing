#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    int isLoggedIn;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void logout(User *user) {
    user->isLoggedIn = 0;
    printf("Logged out successfully.\n");
}

int changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (user->isLoggedIn && strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
        return 1;
    } else {
        printf("Failed to change email. Please check your old email and password.\n");
        return 0;
    }
}

int main() {
    User user = {"john_doe", "john@example.com", "password123", 0};

    char choice, oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Login\n2. Change Email\n3. Logout\n4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Enter email: ");
                scanf("%s", oldEmail);
                printf("Enter password: ");
                scanf("%s", password);
                login(&user, oldEmail, password);
                break;

            case '2':
                if (!user.isLoggedIn) {
                    printf("Please log in first.\n");
                } else {
                    printf("Enter old email: ");
                    scanf("%s", oldEmail);
                    printf("Confirm password: ");
                    scanf("%s", password);
                    printf("Enter new email: ");
                    scanf("%s", newEmail);
                    changeEmail(&user, oldEmail, password, newEmail);
                }
                break;

            case '3':
                logout(&user);
                break;

            case '4':
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}