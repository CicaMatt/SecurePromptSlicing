#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User database[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(username, database[i].username) == 0 && strcmp(password, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Content-Type: text/html\n\n");

    if (fgets(username, sizeof(username), stdin) != NULL && fgets(password, sizeof(password), stdin) != NULL) {
        username[strcspn(username, "\r\n")] = 0; // Remove newline or carriage return
        password[strcspn(password, "\r\n")] = 0; // Remove newline or carriage return

        if (authenticate(username, password)) {
            printf("Location: /home.html\n\n");
        } else {
            printf("Location: /login.html?error=1\n\n");
        }
    } else {
        printf("<html><body>Error reading form data.</body></html>");
    }
}

int main() {
    handle_login();
    return 0;
}