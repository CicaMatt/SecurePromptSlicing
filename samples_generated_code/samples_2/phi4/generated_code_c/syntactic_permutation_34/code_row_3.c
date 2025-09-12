#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"admin", "adminpass"},
    // Add more predefined users here
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("Login successful! Redirecting to dashboard...\n");
        // Code to redirect to the dashboard
    } else {
        printf("Invalid credentials. Redirecting back to login page.\n");
        login_page();
    }
}

int main() {
    login_page();
    return 0;
}