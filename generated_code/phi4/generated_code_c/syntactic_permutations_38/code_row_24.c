#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

const int user_count = sizeof(users) / sizeof(users[0]);

int login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username); // Limit input size for security.

    printf("Enter password: ");
    scanf("%49s", input_password);

    if (login(input_username, input_password)) {
        redirectTo("home_page.html");
    } else {
        redirectTo("login_page.html");
    }

    return 0;
}