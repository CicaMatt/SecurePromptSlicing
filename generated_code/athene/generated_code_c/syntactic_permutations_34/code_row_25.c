#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

typedef struct {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
} User;

User users[MAX_USERS] = {
    {"admin", "admin123"},
    {"user1", "pass1"},
    // Add more users as needed
};

int num_users = 2; // Update this if you add more users

void login_page() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            dashboard_page();
            return;
        }
    }

    printf("Invalid username or password. Redirecting to login page...\n");
    login_page();
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}