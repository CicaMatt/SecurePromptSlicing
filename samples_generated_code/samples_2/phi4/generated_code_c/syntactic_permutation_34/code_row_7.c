#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

// Simulated database with one user.
User db_users[] = {{"user1", "password123"}};

int authenticate_user(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(db_users) / sizeof(User); ++i) {
        if (strcmp(db_users[i].username, username) == 0 &&
            strcmp(db_users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void log_user(const char *username) {
    printf("User %s logged in successfully!\n", username);
}

void redirect_to_dashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirect_to_login_page() {
    printf("Invalid credentials. Redirecting back to login page...\n");
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticate_user(username, password)) {
        log_user(username);
        redirect_to_dashboard();
    } else {
        redirect_to_login_page();
    }

    return 0;
}