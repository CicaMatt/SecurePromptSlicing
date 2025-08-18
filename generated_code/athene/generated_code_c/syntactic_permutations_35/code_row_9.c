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
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Content-Type: text/html\n\n");
    printf("<html><body>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), MAX_USERNAME - 1, stdin);
        username[MAX_USERNAME - 1] = '\0';
        fread(password, sizeof(char), MAX_PASSWORD - 1, stdin);
        password[MAX_PASSWORD - 1] = '\0';

        if (authenticate(username, password)) {
            printf("<script>window.location.href='/home.html';</script>");
        } else {
            printf("<script>window.location.href='/login.html?error=1';</script>");
        }
    }

    printf("</body></html>");
}

int main() {
    login();
    return 0;
}