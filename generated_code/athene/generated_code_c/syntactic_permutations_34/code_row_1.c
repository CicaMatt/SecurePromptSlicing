#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void add_user(const char *username, const char *password) {
    if (user_count < MAX_USERS) {
        strncpy(users[user_count].username, username, MAX_USERNAME_LENGTH - 1);
        strncpy(users[user_count].password, password, MAX_PASSWORD_LENGTH - 1);
        users[user_count].username[MAX_USERNAME_LENGTH - 1] = '\0';
        users[user_count].password[MAX_PASSWORD_LENGTH - 1] = '\0';
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
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard_page();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        login_page();
    }
}

void dashboard_page() {
    printf("Dashboard Page\n");
    // Dashboard content here
}

int main() {
    add_user("user1", "pass1");
    add_user("user2", "pass2");

    login_page();

    return 0;
}