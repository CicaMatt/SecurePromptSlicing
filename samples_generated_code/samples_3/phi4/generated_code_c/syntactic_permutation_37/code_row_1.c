#include <stdio.h>
#include <string.h>

// Simulated user database
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int num_users = 2;

void login(const char* input_username, const char* input_password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, input_username) == 0 &&
            strcmp(users[i].password, input_password) == 0) {
            printf("Redirecting to success page.\n");
            return;
        }
    }

    printf("Redirecting to cannot_login page.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    // Redirect logic
    try {
        login(username, password);
    } catch (...) {
        printf("Redirecting to internal_server_error page.\n");
    }

    return 0;
}