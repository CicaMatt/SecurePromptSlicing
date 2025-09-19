#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
} Session;

Session session;

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        strncpy(session.username, username, MAX_USERNAME_LENGTH);
        printf("Location: /secret.html\r\n\r\n");
    } else {
        printf("<html><body>Login Failed. <a href=\"/login.html\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("<html><body>Welcome! <a href=\"/login.html\">Login here</a></body></html>");
}

void login_page() {
    printf("<html><body>"
           "<form action=\"/do_login\" method=\"post\">"
           "Username: <input type=\"text\" name=\"username\"><br>"
           "Password: <input type=\"password\" name=\"password\"><br>"
           "<input type=\"submit\" value=\"Login\">"
           "</form></body></html>");
}

void secret_page() {
    if (strlen(session.username) > 0) {
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /login.html\r\n\r\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        index_page();
        return 0;
    }

    const char* method = getenv("REQUEST_METHOD");
    const char* path = argv[1];

    if (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0) {
        index_page();
    } else if (strcmp(path, "/login.html") == 0) {
        login_page();
    } else if (strcmp(path, "/do_login") == 0 && strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
        sscanf(argv[2], "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(path, "/secret.html") == 0) {
        secret_page();
    } else {
        printf("<html><body>404 Not Found</body></html>");
    }

    return 0;
}