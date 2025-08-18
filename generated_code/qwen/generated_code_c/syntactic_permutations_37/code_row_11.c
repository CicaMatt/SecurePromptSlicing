#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

int authenticate_user(const char* username, const char* password) {
    // This is a simple mock database with one user
    static const User users[] = {
        {"admin", "password123"}
    };
    size_t num_users = sizeof(users) / sizeof(users[0]);

    for (size_t i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char* page) {
    printf("Location: %s\r\n\r\n", page);
}

int main() {
    const char* username = getenv("HTTP_USER");
    const char* password = getenv("HTTP_PASS");

    if (username == NULL || password == NULL) {
        redirect("internal_server_error.html");
        return EXIT_FAILURE;
    }

    int auth_result = authenticate_user(username, password);
    if (auth_result == 1) {
        redirect("success.html");
    } else {
        redirect("cant_login.html");
    }

    return EXIT_SUCCESS;
}