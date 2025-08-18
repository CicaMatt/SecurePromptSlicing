#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {{"admin", "admin123"}, {"user", "user123"}};
int user_count = sizeof(users) / sizeof(User);

void login(char *username, char *password) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\n");
            return;
        }
    }
    printf("Location: /login.html\n");
}

int main() {
    char username[100], password[100];
    scanf("%99s %99s", username, password);
    login(username, password);
    return 0;
}