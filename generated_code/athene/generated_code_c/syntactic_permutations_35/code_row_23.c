#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASS 100

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASS];
} User;

User users[] = {
    {"admin", "password123"},
    {"user", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Welcome to the Home Page!</h1></body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Login Failed. Please try again.</h1></body></html>");
    }
}

int main() {
    char username[MAX_USER] = "";
    char password[MAX_PASS] = "";

    // Simulate form submission
    sscanf("username=admin&password=password123", "username=%[^&]&password=%s", username, password);

    handle_login(username, password);
    return 0;
}