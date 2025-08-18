#include <stdio.h>
#include <string.h>

// Simulated database with credentials
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50];
    char password[50];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("Redirecting to Dashboard...\n");
    } else {
        printf("Invalid credentials. Redirecting back to Login Page...\n");
    }
}

int main() {
    login_page();
    return 0;
}