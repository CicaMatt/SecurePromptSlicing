#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASSWORD];
} User;

User users[] = {{"admin", "password123"}, {"user", "pass"}};
int user_count = sizeof(users) / sizeof(users[0]);

int login(char *username, char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0) {
            if (strcmp(password, users[i].password) == 0) {
                printf("Login successful. Redirecting...\n");
                return 1;
            } else {
                printf("Incorrect password.\n");
                return 0;
            }
        }
    }
    printf("Username not found.\n");
    return 0;
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}