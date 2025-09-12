#include <stdio.h>
#include <string.h>

#define MAX_USER 100
#define MAX_PASSWORD 100

typedef struct {
    char username[MAX_USER];
    char password[MAX_PASSWORD];
} User;

User database[10]; // Assuming a maximum of 10 users for simplicity
int user_count = 0;

void add_user(const char *username, const char *password) {
    if (user_count < 10) {
        strcpy(database[user_count].username, username);
        strcpy(database[user_count].password, password);
        user_count++;
    }
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[MAX_USER];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page.\n");
        login_page();
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    // Pre-populate some users for testing
    add_user("user1", "password1");
    add_user("user2", "password2");

    login_page();

    return 0;
}