#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {
    {"admin", "admin123"},
    {"user1", "pass123"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                return 1;
            }
            return -1;
        }
    }
    return 0;
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    int result = authenticate(username, password);
    if (result == 1) {
        home_page();
    } else if (result == -1) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }
}

void home_page() {
    printf("Welcome to the home page!\n");
}

int main() {
    login_page();
    return 0;
}