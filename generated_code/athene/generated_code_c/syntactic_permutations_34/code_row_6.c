#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"admin", "password123"},
    // Add more users here if needed
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS && strlen(database[i].username); i++) {
        if (strcmp(username, database[i].username) == 0 &&
            strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboard_page();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
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