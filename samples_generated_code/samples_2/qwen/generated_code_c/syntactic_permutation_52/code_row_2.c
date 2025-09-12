#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: secret_page.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"index.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome</h1>");
    printf("<p><a href=\"login_form.html\">Login</a></p>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "index") == 0) {
            index_page();
        } else if (strcmp(argv[1], "do_login") == 0 && argc == 4) {
            do_login(argv[2], argv[3]);
        } else if (strcmp(argv[1], "secret_page") == 0) {
            secret_page();
        }
    }
    return 0;
}