#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {{"admin", "password123"}, {"user", "pass"}};
int user_count = sizeof(users) / sizeof(User);

void login(char* name, char* password) {
    int found = 0;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(name, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Location: /login.html?error=1\n");
    }
}

int main() {
    char name[50], password[50];
    // Simulate form input
    strcpy(name, "admin");
    strcpy(password, "password123");

    login(name, password);
    return 0;
}