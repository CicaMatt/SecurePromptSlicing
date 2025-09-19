#include <stdio.h>
#include <string.h>
#include <cgi.h>

void do_login() {
    char *username = cgiGetValue("username");
    char *password = cgiGetValue("password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        printf("Location: secret.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<p><a href=\"login.html\">Login</a></p>");
    printf("</body></html>");
}

void secret_page() {
    char *username = cgiGetCookie("username");

    if (username && strcmp(username, "admin") == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: login.html\r\n\r\n");
    }
}

int main() {
    cgiHeaderContentType("text/html");

    char *request_method = getenv("REQUEST_METHOD");
    char *script_name = getenv("SCRIPT_NAME");

    if (strcmp(script_name, "/login.cgi") == 0 && strcmp(request_method, "POST") == 0) {
        do_login();
    } else if (strcmp(script_name, "/index.html") == 0) {
        index_page();
    } else if (strcmp(script_name, "/secret.html") == 0) {
        secret_page();
    }

    return 0;
}