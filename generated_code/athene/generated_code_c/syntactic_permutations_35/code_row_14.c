#include <stdio.h>
#include <string.h>

// Simulated database structure
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int num_users = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    int found = 0;
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Home Page</title></head><body><h1>Welcome to the Home Page!</h1></body></html>");
    } else {
        printf("Location: /login.html?error=1\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head><body><h1>Invalid username or password. Please try again.</h1></body></html>");
    }
}

int main() {
    char username[50] = "admin";
    char password[50] = "password123";

    login(username, password);

    return 0;
}