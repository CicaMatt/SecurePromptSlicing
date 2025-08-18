#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int check_credentials(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_login_request(const char *request) {
    const char *token_start = strstr(request, "username=");
    if (token_start) {
        token_start += strlen("username=");
        const char *token_end = strchr(token_start, '&');
        char username[50];
        if (token_end) {
            strncpy(username, token_start, token_end - token_start);
            username[token_end - token_start] = '\0';
        } else {
            strcpy(username, token_start);
        }

        const char *password_start = strstr(request, "password=");
        if (password_start) {
            password_start += strlen("password=");
            char password[50];
            sscanf(password_start, "password=%49s", password);

            if (check_credentials(username, password)) {
                printf("HTTP/1.1 302 Found\nLocation: /home.html\n\n");
            } else {
                printf("HTTP/1.1 302 Found\nLocation: /login.html\n\n");
            }
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\n"
               "<html><body>Login failed</body></html>\n");
    }
}

int main() {
    const char *request = "GET /login HTTP/1.1\r\n"
                          "Host: localhost\r\n"
                          "Connection: close\r\n"
                          "\r\n"
                          "?username=user1&password=pass1";

    handle_login_request(request);
    return 0;
}