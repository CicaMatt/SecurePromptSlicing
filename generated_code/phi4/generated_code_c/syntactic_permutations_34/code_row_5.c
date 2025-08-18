#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User database[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    if (login(input_username, input_password)) {
        dashboard();
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
    }

    return 0;
}