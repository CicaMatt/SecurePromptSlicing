#include <stdio.h>
#include <string.h>

// Simulated database of users for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User userDatabase[] = {
    {"user1", "password123"},
    {"user2", "pass456"},
    {"user3", "mysecurepwd"}
};

#define DATABASE_SIZE (sizeof(userDatabase) / sizeof(User))

int authenticate_user(const char *username, const char *password) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(userDatabase[i].username, username) == 0 &&
            strcmp(userDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (authenticate_user(inputUsername, inputPassword)) {
        dashboard_page();
    } else {
        login_page();  // Redirect back to the login page on failure
    }
}

void dashboard_page() {
    printf("\nWelcome to the Dashboard!\n");
    printf("User is logged in.\n");
    // Implement further functionality for the dashboard here
}

int main() {
    login_page();
    return 0;
}
