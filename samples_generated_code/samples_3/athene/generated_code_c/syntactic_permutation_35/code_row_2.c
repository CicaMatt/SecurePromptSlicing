#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "userpass"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Home Page</h1>");
        printf("</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Please try again.</p>");
        printf("<a href=\"/login.html\">Back to Login</a>");
        printf("</body></html>");
    }
}

int main() {
    char username[50], password[50];
    scanf("%49s %49s", username, password);
    login(username, password);
    return 0;
}