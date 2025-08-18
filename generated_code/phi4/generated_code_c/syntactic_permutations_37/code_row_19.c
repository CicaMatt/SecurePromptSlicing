#include <stdio.h>
#include <string.h>

#define MAX_USERS 3

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "password1"},
    {"user2", "password2"},
    {"admin", "adminpass"}
};

void redirect(const char *location) {
    printf("Redirecting to: %s\n", location);
}

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char input_username[50], input_password[50];

    printf("Enter username: ");
    if (fgets(input_username, sizeof(input_username), stdin) != NULL) {
        size_t len = strlen(input_username);
        if (len > 0 && input_username[len - 1] == '\n') {
            input_username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(input_password, sizeof(input_password), stdin) != NULL) {
        size_t len = strlen(input_password);
        if (len > 0 && input_password[len - 1] == '\n') {
            input_password[--len] = '\0';
        }
    }

    if (check_credentials(input_username, input_password)) {
        printf("Login successful!\n");
    } else {
        redirect("cant_login");
    }
}

int main() {
    login_page();
    return 0;
}