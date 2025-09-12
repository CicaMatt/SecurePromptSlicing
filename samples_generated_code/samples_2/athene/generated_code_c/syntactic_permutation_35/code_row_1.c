#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
    } else {
        printf("Location: /login.html?error=1\n");
    }
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[MAX_USERNAME] = "";
    char password[MAX_PASSWORD] = "";

    // Simulate form data
    const char *form_data = "username=admin&password=password123";

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    handle_login(username, password);

    return 0;
}