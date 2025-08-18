#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin"}
};

int user_count = 3;

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Redirecting to home page...\n");
            return;
        }
    }
    printf("Invalid credentials. Redirecting back to login page...\n");
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    login(input_username, input_password);

    return 0;
}