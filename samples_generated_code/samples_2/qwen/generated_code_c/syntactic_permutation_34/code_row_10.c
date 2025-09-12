#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int user_count = sizeof(database) / sizeof(User);

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your username: ");
    scanf("%49s", username);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard_page();
    } else {
        login_page();
    }
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}