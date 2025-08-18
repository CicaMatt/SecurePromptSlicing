#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User userDatabase[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int userCount = 2;

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i].username, username) == 0 &&
            strcmp(userDatabase[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboardPage();
    } else {
        printf("Login Failed. Redirecting back to login page.\n");
        loginPage();
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}