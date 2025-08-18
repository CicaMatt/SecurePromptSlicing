#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {
    {"alice", "password123"},
    {"bob", "securepass"}
};

int login(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(database[0]); ++i) {
        if (strcmp(database[i].username, username) == 0) {
            if (strcmp(database[i].password, password) == 0) {
                return 1;
            } else {
                return -1;
            }
        }
    }
    return 0;
}

void handle_login() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int result = login(username, password);

    if (result == 1) {
        printf("Login successful. Redirecting to home page...\n");
    } else if (result == -1) {
        printf("Incorrect password.\n");
    } else {
        printf("Username not found.\n");
    }
}

int main() {
    handle_login();
    return 0;
}