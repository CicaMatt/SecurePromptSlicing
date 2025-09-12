#include <stdio.h>
#include <string.h>
#include <cgi/cgi.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login() {
    char *username = cgiFormString("username");
    char *password = cgiFormString("password");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        printf("Location: /secret\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h2>Secret settings</h2>");
    printf("</body></html>");
}

int main(void) {
    cgiHeaderContentType("text/html");

    char *request_method = getenv("REQUEST_METHOD");
    char *path_info = getenv("PATH_INFO");

    if (strcmp(request_method, "POST") == 0 && strcmp(path_info, "/login") == 0) {
        do_login();
    } else if (strcmp(path_info, "/secret") == 0) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}