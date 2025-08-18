#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASS 100

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASS];
} User;

User users[] = {{"user1", "pass1"}, {"user2", "pass2"}};
int user_count = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Location: /home.html\n");
            printf("\n");
            return;
        }
    }
    printf("Location: /login.html?error=1\n");
    printf("\n");
}

int main() {
    char username[MAX_USER] = "";
    char password[MAX_PASS] = "";

    // Simulate reading from HTTP POST request
    strcpy(username, "user1"); // Example input
    strcpy(password, "pass1"); // Example input

    login(username, password);

    return 0;
}