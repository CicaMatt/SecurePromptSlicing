#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define DATABASE_SIZE 10

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[DATABASE_SIZE] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (login(username, password)) {
        printf("Login successful. Redirecting to home page.\n");
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        handle_login();
    }
}

int main() {
    handle_login();
    return 0;
}