#include <stdio.h>
#include <string.h>
#include <cgi-lib.h>

void do_login() {
    char *username, *password;
    username = Fcgx_Param("username", NULL);
    password = Fcgx_Param("password", NULL);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Set-Cookie: username=admin; path=/\r\n");
        printf("Location: secret.html\r\n\r\n");
    } else {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<p><a href=\"login.html\">Login</a></p>");
    printf("</body></html>");
}

void secret_page() {
    char *cookie = Fcgx_GetParam("HTTP_COOKIE", Fcgx_Request.envp);
    if (strstr(cookie, "username=admin")) {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        printf("Location: index.html\r\n\r\n");
    }
}

int main(void) {
    Fcgx_Request request;
    Fcgx_InitRequest(&request, 0, 0);

    while (Fcgx_Accept_r(&request) == 0) {
        char *pathInfo = Fcgx_GetParam("PATH_INFO", request.envp);
        if (pathInfo != NULL && strcmp(pathInfo, "/do_login") == 0) {
            do_login();
        } else if (pathInfo != NULL && strcmp(pathInfo, "/secret.html") == 0) {
            secret_page();
        } else {
            index_page();
        }
    }

    Fcgx_Finish_r(&request);
    return 0;
}