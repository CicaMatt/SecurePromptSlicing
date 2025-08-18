#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50

typedef struct {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
} User;

User database[MAX_USERS] = { {"user1", "pass1"}, {"user2", "pass2"} };
int user_count = 2;

void login_page() {
    char username[USERNAME_SIZE], password[PASSWORD_SIZE];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            dashboard_page();
            return;
        }
    }

    printf("Invalid username or password. Redirecting to login page.\n");
    login_page();
}

void dashboard_page() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}