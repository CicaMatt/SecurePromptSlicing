#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {
    {"john", "1234"},
    {"jane", "5678"}
};

int num_users = sizeof(users) / sizeof(users[0]);

void login(char *username, char *password) {
    int i;
    for (i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: home.html\n");
            printf("Content-Type: text/html\n\n");
            printf("<html><body>You are logged in!</body></html>");
            return;
        }
    }
    printf("Location: login.html\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Login failed. Please try again.</body></html>");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate form submission
    sscanf("username=john&password=1234", "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}