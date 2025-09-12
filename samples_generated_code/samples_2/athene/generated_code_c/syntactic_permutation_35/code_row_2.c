#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {{"admin", "1234"}, {"user", "password"}};
int user_count = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\n");
            printf("Content-Type: text/html\n\n");
            return;
        }
    }
    printf("Location: /login.html\n");
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulate form data
    strcpy(username, getenv("username"));
    strcpy(password, getenv("password"));

    login(username, password);
    return 0;
}