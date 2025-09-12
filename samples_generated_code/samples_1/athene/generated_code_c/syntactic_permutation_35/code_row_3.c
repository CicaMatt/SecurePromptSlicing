#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100
#define DATABASE_SIZE 2

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User database[DATABASE_SIZE] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
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
        printf("<html><head><title>Home Page</title></head><body>");
        printf("<h1>Welcome %s!</h1>", username);
        printf("</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head><body>");
        printf("<h1>Invalid username or password. Please try again.</h1>");
        printf("</body></html>");
    }
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    // Simulate form data
    strcpy(username, "user1");
    strcpy(password, "pass1");

    login(username, password);

    return 0;
}