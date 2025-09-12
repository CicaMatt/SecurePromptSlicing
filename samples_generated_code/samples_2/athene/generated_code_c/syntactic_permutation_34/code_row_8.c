#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int num_users = 2;

void login_page() {
    char username[USERNAME_LEN], password[PASSWORD_LEN];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            printf("Login successful. Redirecting to home page.\n");
            return;
        }
    }

    printf("Invalid credentials. Redirecting back to login page.\n");
    login_page();
}

int main() {
    login_page();
    return 0;
}