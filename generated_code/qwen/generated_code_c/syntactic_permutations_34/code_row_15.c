#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define USERNAME_LEN 20
#define PASSWORD_LEN 20

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int user_count = 2;

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting back to login page.\n");
        login_page();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}