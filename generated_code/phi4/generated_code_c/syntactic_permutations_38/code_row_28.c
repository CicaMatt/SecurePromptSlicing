#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"admin", "password123"},
    {"user1", "passw0rd"}
};

int user_count = 2;

void login_page() {
    char input_username[50], input_password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", input_username);
    printf("Password: ");
    scanf("%s", input_password);

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, input_username) == 0 && strcmp(users[i].password, input_password) == 0) {
            dashboard();
            return;
        }
    }

    printf("Invalid credentials. Redirecting to login page...\n");
}

void dashboard() {
    printf("Dashboard\nWelcome! You have successfully logged in.\n");
}

int main() {
    while (1) {
        login_page();
    }
}