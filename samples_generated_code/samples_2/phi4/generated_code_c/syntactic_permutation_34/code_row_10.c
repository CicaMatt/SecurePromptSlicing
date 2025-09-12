#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Simulated database with user credentials
User users_db[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int validate_login(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users_db) / sizeof(users_db[0]); ++i) {
        if (strcmp(users_db[i].username, username) == 0 && strcmp(users_db[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void log_user() {
    printf("Redirecting to dashboard...\n");
    // Code for redirecting to the dashboard would go here
}

void login_page() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (validate_login(username, password)) {
        log_user();
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // Code for redirecting back to the login page would go here
    }
}

int main() {
    login_page();
    return 0;
}