#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

typedef struct {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
} User;

User users[MAX_USERS];
int user_count = 0;

void add_user(const char *username, const char *password) {
    if (user_count < MAX_USERS) {
        strncpy(users[user_count].username, username, USERNAME_MAX_LEN - 1);
        strncpy(users[user_count].password, password, PASSWORD_MAX_LEN - 1);
        user_count++;
    }
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid username or password.\n");
        login_page();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    add_user("user1", "pass1");
    add_user("user2", "pass2");

    login_page();

    return 0;
}