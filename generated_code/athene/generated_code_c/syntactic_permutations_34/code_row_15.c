#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(User); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        login();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login();
    return 0;
}