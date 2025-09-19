#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {
    {"admin", "password123"},
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(database[0]); ++i) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>You are logged in!</body></html>");
    } else {
        printf("Location: /login.html?error=1\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Login failed. Please try again.</body></html>");
    }
}

int main() {
    char username[MAX_USERNAME_LEN] = "";
    char password[MAX_PASSWORD_LEN] = "";

    // Simulate form data (normally this would come from CGI environment variables)
    const char *form_data = "username=admin&password=password123";

    // Parse form data
    sscanf(form_data, "username=%99[^&]&password=%99s", username, password);

    login(username, password);

    return 0;
}