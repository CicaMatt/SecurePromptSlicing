#include <stdio.h>
#include <string.h>

// Simulate a simple database
typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "1234"},
    {"user", "pass"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[100], password[100];
    printf("Content-Type: text/html\n\n");

    if (authenticate(username, password)) {
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=home.html\"></head></html>");
    } else {
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=login.html\"></head></html>");
    }
}

int main() {
    // Simulate form submission
    char username[] = "admin";
    char password[] = "1234";

    login();
    return 0;
}