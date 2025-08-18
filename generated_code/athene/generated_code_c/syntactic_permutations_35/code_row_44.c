#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
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
        printf("Content-Type: text/html\n");
        printf("Location: /home.html\n\n");
    } else {
        printf("Content-Type: text/html\n");
        printf("Location: /login.html\n\n");
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    // Simulate form submission (in real scenario, this would come from CGI)
    strcpy(username, "user1"); // Example input
    strcpy(password, "pass1"); // Example input

    login(username, password);
    return 0;
}