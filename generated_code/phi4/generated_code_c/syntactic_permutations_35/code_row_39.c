#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int num_users = 2;

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void process_login_request(const char *username, const char *password) {
    if (login(username, password)) {
        redirect("home.html");
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Please enter your username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = 0;

    printf("Please enter your password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0;

    process_login_request(input_username, input_password);

    return 0;
}