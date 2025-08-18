#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        login_page();
    }
}

int main() {
    login_page();
    return 0;
}