#include <stdio.h>
#include <string.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"admin", "admin"}
};

int login(const char *username, const char *password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void handle_request(const char *request) {
    const char *start = strstr(request, "username=");
    const char *end = start ? strchr(start, '&') : NULL;
    if (!start || !end) return;

    size_t len = end - (start + 9);
    char username[50];
    strncpy(username, start + 9, len);
    username[len] = '\0';

    start = strstr(request, "password=");
    end = start ? strchr(start, ' ') : NULL;
    if (!start || !end) return;

    len = end - (start + 9);
    char password[50];
    strncpy(password, start + 9, len);
    password[len] = '\0';

    if (login(username, password)) {
        printf("HTTP/1.1 303 See Other\nLocation: /home.html\nContent-Type: text/html; charset=UTF-8\n\n");
        printf("<html><head><title>Redirecting...</title></head><body>\n"
               "<p>You are being redirected to the home page.</p>\n"
               "</body></html>");
    } else {
        printf("HTTP/1.1 303 See Other\nLocation: /login.html\nContent-Type: text/html; charset=UTF-8\n\n");
        printf("<html><head><title>Redirecting...</title></head><body>\n"
               "<p>Login failed. Redirecting back to login page.</p>\n"
               "</body></html>");
    }
}

int main() {
    const char *request = "POST /login HTTP/1.1\nHost: localhost\nContent-Type: application/x-www-form-urlencoded\nContent-Length: 33\n\nusername=user1&password=pass1";
    handle_request(request);
    return 0;
}