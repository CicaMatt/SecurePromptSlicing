#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Set-Cookie: username=%s; Path=/\n", username);
        printf("Location: /secret\n\n");
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/secret\"></head><body></body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a>.</body></html>");
    }
}

void index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome! Please <a href=\"/login\">log in</a> to access the secret page.</body></html>");
}

void secret() {
    char username[100] = "";
    printf("Content-Type: text/html\n\n");

    // Simple cookie parsing (not secure, for demonstration purposes)
    char *cookie = getenv("HTTP_COOKIE");
    if (cookie && sscanf(cookie, "username=%99s", username) == 1) {
        printf("<html><body>Welcome %s! This is the secret page.</body></html>", username);
    } else {
        printf("<html><body>You are not logged in. <a href=\"/login\">Log in</a> to view this page.</body></html>");
    }
}

int main() {
    const char *script_name = getenv("SCRIPT_NAME");

    if (strcmp(script_name, "/login") == 0) {
        char username[100] = "", password[100] = "";
        sscanf(getenv("QUERY_STRING"), "username=%99[^&]&password=%99s", username, password);
        do_login(username, password);
    } else if (strcmp(script_name, "/index") == 0) {
        index();
    } else if (strcmp(script_name, "/secret") == 0) {
        secret();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>404 Not Found</body></html>");
    }

    return 0;
}