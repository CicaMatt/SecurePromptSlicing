#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {{"john", "1234"}, {"alice", "5678"}};
int user_count = sizeof(users) / sizeof(User);

int login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0) {
            if (strcmp(password, users[i].password) == 0) {
                return 1;
            }
            return 0;
        }
    }
    return -1;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int result = login(username, password);

    if (result == 1) {
        printf("Login successful.\n");
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }

    return 0;
}