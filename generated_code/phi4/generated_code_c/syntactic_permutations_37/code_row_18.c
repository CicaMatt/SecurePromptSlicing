#include <stdio.h>
#include <string.h>

// Simulated database entries for demonstration
typedef struct {
    const char *username;
    const char *password;
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int user_count = sizeof(users) / sizeof(User);

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

void login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            redirect("success");
            return;
        }
    }
    redirect("cant_login");
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    try {
        login(username, password);
    } catch (...) {
        redirect("internal_server_error");
    }

    return 0;
}