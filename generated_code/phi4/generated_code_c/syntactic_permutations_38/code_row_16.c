#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

// Mock database with one user for demonstration purposes.
User users[] = {
    {"admin", "password123"}
};

int authenticate(const char *username, const char *password) {
    int num_users = sizeof(users) / sizeof(users[0]);
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void show_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void login_page() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        show_dashboard();
    } else {
        printf("Incorrect Username or Password. Redirecting to Login Page...\n");
        login_page(); // Recursive call to simulate redirection
    }
}

int main() {
    while(1) {  // Infinite loop to keep the program running for multiple login attempts.
        login_page();
    }

    return 0;
}