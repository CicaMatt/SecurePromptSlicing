#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int check_login(const char *username, const char *password) {
    int num_users = sizeof(users) / sizeof(users[0]);
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (check_login(username, password)) {
        printf("Login successful. Redirecting to home page...\n");
        // Simulate redirection
        printf("[Redirect: /home.html]\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Simulate redirection
        printf("[Redirect: /login.html]\n");
    }
}

int main() {
    login();
    return 0;
}