#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"admin", "adminpass"}
};

int login(const char* username, const char* password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

int do_login(const char* username, const char* password) {
    printf("POST request to login with username: %s\n", username);
    if (login(username, password)) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid credentials.\n");
        return 0;
    }
}

void index() {
    printf("Welcome to the homepage!\n");
}

void user_page(const char* username) {
    printf("User page for: %s\n", username);
}

void admin_page(const char* username) {
    if (strcmp(username, "admin") == 0) {
        printf("Admin page for: %s\n", username);
    } else {
        printf("Access denied. Only admins can access this page.\n");
    }
}

int main() {
    const char* username = "user1";
    const char* password = "pass1";

    if (do_login(username, password)) {
        index();
        user_page(username);

        const char* admin_username = "admin";
        const char* admin_password = "adminpass";

        if (do_login(admin_username, admin_password)) {
            admin_page(admin_username);
        }
    }

    return 0;
}