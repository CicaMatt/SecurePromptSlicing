#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User users[] = {
    {"admin", "1234"},
    {"user", "password"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
    } else {
        printf("Location: /login.html?error=1\n");
    }
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "";
    char password[MAX_PASSWORD_LENGTH] = "";

    // Simulate form data (in a real CGI application, this would come from the environment)
    const char *form_data = "username=admin&password=1234";

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);

    return 0;
}