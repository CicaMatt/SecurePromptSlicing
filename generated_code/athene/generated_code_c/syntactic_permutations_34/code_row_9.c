#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User database[MAX_USERS];
int user_count = 0;

void add_user(const char *username, const char *password) {
    if (user_count < MAX_USERS) {
        strncpy(database[user_count].username, username, USERNAME_LENGTH - 1);
        strncpy(database[user_count].password, password, PASSWORD_LENGTH - 1);
        user_count++;
    }
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard_page();
    } else {
        printf("Invalid credentials. Please try again.\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
    // Add dashboard functionality here
}

int main() {
    add_user("user1", "pass1");
    add_user("user2", "pass2");

    login_page();

    return 0;
}