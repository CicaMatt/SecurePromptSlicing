#include <stdio.h>
#include <string.h>
#include <cgi.h>

void do_login() {
    char *username = cgiFormString("username");
    char *password = cgiFormString("password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        printf("Location: /secret.html\r\n");
    } else {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. <a href=\"/login.html\">Try again</a>.</p>");
        printf("</body></html>");
    }
}

int main(void) {
    cgiHeaderContentType("text/html");

    if (cgiInitialize(NULL)) return 1;

    char *script_name = getenv("SCRIPT_NAME");
    if (strcmp(script_name, "/index.html") == 0) {
        printf("<html><body>");
        printf("<p>Welcome! <a href=\"/login.html\">Login</a></p>");
        printf("</body></html>");
    } else if (strcmp(script_name, "/login.cgi") == 0) {
        do_login();
    } else if (strcmp(script_name, "/secret.html") == 0) {
        char *cookie = getenv("HTTP_COOKIE");
        if (strstr(cookie, "username=")) {
            printf("<html><body>");
            printf("<h1>Secret settings</h1>");
            printf("</body></html>");
        } else {
            printf("Location: /login.html\r\n");
        }
    }

    cgiTerminate();
    return 0;
}