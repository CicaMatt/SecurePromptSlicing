#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Set-Cookie: username=%s; path=/\n", username);
        printf("Location: /secret\n");
        printf("\n");
    } else {
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Incorrect username or password.</p>");
        printf("<a href=\"/\">Back to Login</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void login_page() {
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page() {
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        index_page();
        return 0;
    }

    const char *path = argv[1];

    if (strcmp(path, "/login") == 0) {
        login_page();
    } else if (strcmp(path, "/do_login") == 0) {
        const char *username = getenv("HTTP_POST_USERNAME");
        const char *password = getenv("HTTP_POST_PASSWORD");
        do_login(username, password);
    } else if (strcmp(path, "/secret") == 0) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}