#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"}
};

int num_users = 3;

void login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Redirecting to home page...\n");
            return;
        }
    }
    printf("Redirecting to login page...\n");
}

void simulate_login_form(const char *input_username, const char *input_password) {
    printf("Processing form submission...\n");
    login(input_username, input_password);
}

int main() {
    // Simulate form data from "login.html"
    const char *username = "user1";
    const char *password = "pass1";

    simulate_login_form(username, password);

    return 0;
}