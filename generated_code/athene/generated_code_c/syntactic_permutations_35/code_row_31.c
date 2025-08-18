#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int num_users = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\r\n");
            return;
        }
    }
    printf("Location: /login.html?error=1\r\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate reading from form data
    sscanf("username=admin&password=password123", "username=%[^&]&password=%s", username, password);

    printf("Content-Type: text/html\r\n");
    login(username, password);
    return 0;
}