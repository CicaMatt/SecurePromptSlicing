#include <stdio.h>
#include <string.h>
#include <cgi/cgi.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login() {
    char *username = cgi_param("username");
    char *password = cgi_param("password");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s; path=/\n", username);
        printf("Location: /secret.cgi\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Incorrect username or password.</p>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Secret settings</h1>");
    printf("</body></html>");
}

int main(void) {
    cgi_init();

    if (cgi_param("username") && cgi_param("password")) {
        do_login();
    } else {
        index_page();
    }

    return 0;
}