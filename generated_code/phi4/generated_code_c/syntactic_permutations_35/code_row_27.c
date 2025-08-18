#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

// Hardcoded list of users for demonstration purposes
User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int num_users = 2;

void handle_login_request(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Redirect to home page\n");
            return;
        }
    }
    printf("Redirect to login page\n");
}

int main() {
    char username[50] = "user1";
    char password[50] = "password1";

    handle_login_request(username, password);

    return 0;
}