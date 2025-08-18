#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {{"admin", "password"}, {"user1", "pass123"}};
int user_count = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\n");
            printf("Content-Type: text/html\n\n");
            printf("<html><body>Logged in successfully!</body></html>\n");
            return;
        }
    }
    printf("Location: /login.html\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Login failed. Please try again.</body></html>\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate form submission
    strcpy(username, "admin"); // Replace with actual form data retrieval
    strcpy(password, "password"); // Replace with actual form data retrieval

    login(username, password);

    return 0;
}