#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int user_count = sizeof(users) / sizeof(User);

void redirect(const char *url) {
    printf("Redirecting to %s\n", url);
}

int check_login(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login_page() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin)) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    try {
        if (check_login(username, password)) {
            redirect("success");
        } else {
            redirect("cant_login");
        }
    } catch (...) {
        redirect("internal_server_error");
    }
}

int main() {
    login_page();
    return 0;
}