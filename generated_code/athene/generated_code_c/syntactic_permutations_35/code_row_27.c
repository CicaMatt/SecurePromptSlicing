#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"admin", "password123"}, {"user", "pass"}};
int user_count = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: home.html\n");
            return;
        }
    }
    printf("Location: login.html\n");
}

int main() {
    char username[50];
    char password[50];

    // Simulate form data
    strcpy(username, "admin");
    strcpy(password, "password123");

    login(username, password);
    return 0;
}