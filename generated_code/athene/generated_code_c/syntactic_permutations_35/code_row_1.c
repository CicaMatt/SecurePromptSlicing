#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char password[100];
} User;

User users[] = {{"admin", "admin123"}, {"user", "password"}};
int user_count = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: home.html\n\n");
            return;
        }
    }
    printf("Location: login.html?error=1\n\n");
}

int main() {
    char username[100], password[100];
    sscanf(getenv("QUERY_STRING"), "username=%[^&]&password=%s", username, password);
    login(username, password);
    return 0;
}