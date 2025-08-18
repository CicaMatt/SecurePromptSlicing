#include <stdio.h>
#include <string.h>

// Simulate a simple in-memory "database"
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"admin", "password123"}, {"user", "pass"}};
int user_count = sizeof(users) / sizeof(User);

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\n");
            return;
        }
    }
    printf("Location: /login.html\n");
}

int main() {
    char username[50];
    char password[50];

    // Simulate form submission
    fgets(username, sizeof(username), stdin);
    fgets(password, sizeof(password), stdin);

    // Remove newline characters if present
    username[strcspn(username, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;

    login(username, password);
    return 0;
}