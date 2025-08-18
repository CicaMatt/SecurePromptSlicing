#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"admin", "password"},
    // Add more users if needed
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS && strlen(users[i].username) > 0; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50], password[50];
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting back to login page.\n");
        login_page();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
    // Add dashboard functionality here
}

int main() {
    login_page();
    return 0;
}