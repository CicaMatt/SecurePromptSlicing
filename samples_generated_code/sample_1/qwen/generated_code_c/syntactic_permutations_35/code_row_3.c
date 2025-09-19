#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User database[MAX_USERS];
int user_count = 0;

void add_user(const char *username, const char *password) {
    if (user_count < MAX_USERS) {
        strcpy(database[user_count].username, username);
        strcpy(database[user_count].password, password);
        user_count++;
    }
}

int check_credentials(const char *name, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, name) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *name, const char *password) {
    if (check_credentials(name, password)) {
        printf("Redirecting to home page...\n");
        // In a real application, you would perform the redirection here.
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // In a real application, you would perform the redirection here.
    }
}

int main() {
    // Pre-populate database with some users for demonstration
    add_user("user1", "pass1");
    add_user("admin", "admin");

    // Simulating form input
    const char *username_input = "user1";
    const char *password_input = "pass1";

    login(username_input, password_input);

    return 0;
}