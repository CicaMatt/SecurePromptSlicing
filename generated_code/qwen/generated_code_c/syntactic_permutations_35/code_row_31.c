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

void add_user(const char *username, const char *password) {
    if (user_count < MAX_USERS) {
        strcpy(users[user_count].username, username);
        strcpy(users[user_count].password, password);
        user_count++;
    }
}

int check_login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void simulate_login(const char *username, const char *password) {
    if (check_login(username, password)) {
        printf("HTTP/1.1 302 Found\nLocation: /home.html\nContent-Type: text/html\n\n");
    } else {
        printf("HTTP/1.1 302 Found\nLocation: /login.html\nContent-Type: text/html\n\n");
    }
}

int main() {
    add_user("user1", "pass1");
    add_user("admin", "admin");

    const char *username = getenv("QUERY_STRING_USERNAME");
    const char *password = getenv("QUERY_STRING_PASSWORD");

    if (username && password) {
        simulate_login(username, password);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\nInvalid request\n");
    }

    return 0;
}