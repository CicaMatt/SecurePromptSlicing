#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[] = {{"admin", "password123"}, {"user", "pass"}};
int user_count = sizeof(users) / sizeof(User);

void login(char *username, char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: home.html\r\n");
            return;
        }
    }
    printf("Location: login.html?error=1\r\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    // Simulate form data
    const char *form_data = "username=admin&password=password123";

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}