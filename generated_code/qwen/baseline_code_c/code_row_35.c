#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users() {
    // This function would typically load users from a database or file
    strcpy(users[user_count].username, "admin");
    strcpy(users[user_count++].password, "admin123");
}

int check_login(const char* username, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void simulate_login(const char* username, const char* password) {
    if (check_login(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Redirecting to login page...\n");
    }
}

int main() {
    load_users();

    // Simulating form input
    const char* username = "admin";
    const char* password = "admin123";

    simulate_login(username, password);

    return 0;
}