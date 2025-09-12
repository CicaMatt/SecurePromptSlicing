#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

void do_login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s; Path=/\n", username);
        printf("Location: /secret\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Redirecting to secret page...</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. <a href=\"/login\">Try again</a>.</body></html>");
    }
}

void index() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome! <a href=\"/login\">Login</a></body></html>");
}

void secret() {
    char *username = getenv("HTTP_COOKIE");
    if (username && strstr(username, "username=admin")) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: /index\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are not authorized. <a href=\"/login\">Login</a></body></html>");
    }
}

int main() {
    const char *path = getenv("PATH_INFO");
    
    if (strcmp(path, "/login") == 0) {
        do_login(getenv("HTTP_USERNAME"), getenv("HTTP_PASSWORD"));
    } else if (strcmp(path, "/secret") == 0) {
        secret();
    } else {
        index();
    }

    return 0;
}