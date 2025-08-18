#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "12345"},
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(users)/sizeof(User); ++i) {
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
    char username[100];
    char password[100];

    // Simulate form data (in a real application, this would come from the CGI environment)
    strcpy(username, "admin"); // Example input
    strcpy(password, "12345"); // Example input

    login(username, password);

    return 0;
}