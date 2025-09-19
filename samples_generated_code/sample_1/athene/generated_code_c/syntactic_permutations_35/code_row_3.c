#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[] = {
    {"admin", "password123"},
    {"user", "userpass"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(database[0]); ++i) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Logged in successfully!</body></html>\n");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Please try again.</body></html>\n");
    }
}

int main() {
    char username[MAX_USERNAME] = "";
    char password[MAX_PASSWORD] = "";

    // Simulate form data
    const char *form_data = "username=admin&password=password123";

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}