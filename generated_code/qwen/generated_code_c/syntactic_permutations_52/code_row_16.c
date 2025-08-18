#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Successful</h1>");
        printf("<p>Redirecting to secret page...</p>");
        printf("<script>window.location.href='secret.html';</script>");
        printf("</body></html>");
    } else {
        printf("Content-type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"index.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"login.html\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret Settings</h1>");
    printf("<p>This is a secret page.</p>");
    printf("</body></html>");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        index_page();
        return 0;
    }

    if (strcmp(argv[1], "login") == 0 && argc == 4) {
        do_login(argv[2], argv[3]);
    } else if (strcmp(argv[1], "secret") == 0) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}