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
    {"user1", "pass456"}
};
int user_count = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /dashboard.html\r\n");
            printf("\r\n");
            return;
        }
    }
    printf("Location: /login.html?error=1\r\n");
    printf("\r\n");
}

int main() {
    char username[MAX_USER] = "admin";
    char password[MAX_PASS] = "password123";

    // Simulate form submission
    login(username, password);

    return 0;
}