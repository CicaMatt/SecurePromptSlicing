#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User database[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int user_count = 2;

void login() {
    char input_username[USERNAME_LENGTH];
    char input_password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", input_username); // Limiting input to prevent overflow

    printf("Enter password: ");
    scanf("%49s", input_password);

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, input_username) == 0 &&
            strcmp(database[i].password, input_password) == 0) {
            printf("Login successful! Redirecting to dashboard...\n");
            // Code to redirect to dashboard
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    // Code to redirect back to login page
}

int main() {
    while (1) {
        login();
        char choice;
        printf("Do you want to retry? (y/n): ");
        scanf(" %c", &choice); // Space before %c to consume newline character

        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    return 0;
}