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

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int user_count = 2;

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Redirect to home page\n");
    } else {
        printf("Redirect to login page\n");
    }
}

int main() {
    // Simulating form submission
    const char *username = "user1";
    const char *password = "pass1";

    login(username, password);

    return 0;
}