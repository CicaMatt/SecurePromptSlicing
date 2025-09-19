#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database)/sizeof(database[0]); ++i) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
    } else {
        printf("Location: /login.html\n");
    }
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[MAX_USERNAME_LEN] = "";
    char password[MAX_PASSWORD_LEN] = "";

    // Simulate reading from form data
    sscanf("username=admin&password=password123", "username=%[^&]&password=%s", username, password);

    handle_login(username, password);
    return 0;
}