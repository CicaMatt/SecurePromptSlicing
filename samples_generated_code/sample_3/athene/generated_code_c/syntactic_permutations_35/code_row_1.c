#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass1"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Welcome to the Home Page</h1></body></html>");
    } else {
        printf("Location: login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Login Failed. Please try again.</h1></body></html>");
    }
}

int main() {
    char username[MAX_USERNAME_LEN] = "";
    char password[MAX_PASSWORD_LEN] = "";

    // Simulate form data
    const char *form_data = "username=admin&password=password123";

    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}