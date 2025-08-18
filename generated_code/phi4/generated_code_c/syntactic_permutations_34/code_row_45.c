#include <stdio.h>
#include <string.h>

// Function prototypes
int check_credentials(const char *username, const char *password);
void login_page();

// Main database simulation
#define MAX_USERS 3

struct User {
    char username[50];
    char password[50];
};

struct User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char input_username[50];
    char input_password[50];

    printf("Enter Username: ");
    scanf("%49s", input_username);
    printf("Enter Password: ");
    scanf("%49s", input_password);

    if (check_credentials(input_username, input_password)) {
        printf("Login successful! Redirecting to dashboard...\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    login_page();
    return 0;
}