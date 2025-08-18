#include <stdio.h>
#include <string.h>

#define MAX_USERS 5

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"},
    {"user4", "pass4"},
    {"user5", "pass5"}
};

int authenticate(char* username, char* password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect_to_dashboard() {
    printf("Redirecting to dashboard...\n");
    // Simulate the redirection logic
}

void redirect_to_login_page() {
    printf("Redirecting to login page. Incorrect username or password.\n");
    // Simulate the redirection logic
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0; // Remove newline character

    if (authenticate(input_username, input_password)) {
        redirect_to_dashboard();
    } else {
        redirect_to_login_page();
    }

    return 0;
}