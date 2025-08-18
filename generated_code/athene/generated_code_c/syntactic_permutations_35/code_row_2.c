#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[] = {{"admin", "1234"}, {"user", "pass"}};
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
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    // Simulate form data
    strcpy(username, "admin"); // Replace with actual form data retrieval
    strcpy(password, "1234");  // Replace with actual form data retrieval

    login(username, password);

    return 0;
}