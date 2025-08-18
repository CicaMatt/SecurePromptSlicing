#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char password[100];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
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
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Redirecting to home page...</body></html>");
    } else {
        printf("Location: /login.html?error=1\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid username or password. Redirecting back to login page...</body></html>");
    }
}

int main() {
    char *username = "user1"; // Example input, normally this would come from form data
    char *password = "pass1"; // Example input, normally this would come from form data

    login(username, password);

    return 0;
}