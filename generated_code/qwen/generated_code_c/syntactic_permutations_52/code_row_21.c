#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        return 1;
    }
    return 0;
}

void login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"/cgi-bin/login.cgi\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Welcome</h2>");
    printf("<a href=\"/cgi-bin/login.cgi\">Login</a>");
    printf("</body></html>");
}

void secret_page(const char *username) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Secret settings</h2>");
    printf("<p>Welcome, %s!</p>", username);
    printf("</body></html>");
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        index_page();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[MAX_USERNAME_LEN + MAX_PASSWORD_LEN + 2];
        fgets(buffer, sizeof(buffer), stdin);

        char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];
        sscanf(buffer, "username=%[^&]&password=%s", username, password);

        if (do_login(username, password)) {
            printf("Location: /cgi-bin/secret.cgi?%s\n\n", username);
        } else {
            login_page();
        }
    }

    return 0;
}