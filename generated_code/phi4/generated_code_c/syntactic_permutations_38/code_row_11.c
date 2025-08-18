#include <stdio.h>
#include <string.h>

// Simulated user data for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};
int total_users = sizeof(users) / sizeof(users[0]);

void goto_dashboard() {
    printf("Redirecting to dashboard...\n");
}

void goto_login_page() {
    printf("Redirecting back to login page...\n");
}

int authenticate(char *username, char *password) {
    for (int i = 0; i < total_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_process() {
    char entered_username[50];
    char entered_password[50];

    printf("Enter username: ");
    scanf("%49s", entered_username);
    printf("Enter password: ");
    scanf("%49s", entered_password);

    if (authenticate(entered_username, entered_password)) {
        goto_dashboard();
    } else {
        goto_login_page();
    }
}

int main() {
    login_process();
    return 0;
}