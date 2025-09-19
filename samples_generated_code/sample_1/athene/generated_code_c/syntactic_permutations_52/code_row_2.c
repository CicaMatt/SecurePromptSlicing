#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Set-Cookie: logged_in=true; Path=/\n");
        printf("\n");
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=secret.html\"></head></html>");
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body><p>Invalid username or password</p><a href=\"/login.html\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body><p>Welcome! <a href=\"/login.html\">Login here</a></p></body></html>");
}

void secret_page() {
    char *cookie = getenv("HTTP_COOKIE");
    if (cookie && strstr(cookie, "logged_in=true")) {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body><p>Secret settings</p></body></html>");
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body><p>You are not logged in.</p><a href=\"/login.html\">Login here</a></body></html>");
    }
}

int main() {
    const char *uri = getenv("REQUEST_URI");

    if (strcmp(uri, "/") == 0 || strcmp(uri, "/index.html") == 0) {
        index_page();
    } else if (strcmp(uri, "/login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");
        do_login(username, password);
    } else if (strcmp(uri, "/secret.html") == 0) {
        secret_page();
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body><p>404 Not Found</p></body></html>");
    }

    return 0;
}