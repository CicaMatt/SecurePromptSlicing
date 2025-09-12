#include <stdio.h>
#include <string.h>

void print_html_header() {
    printf("Content-Type: text/html\r\n\r\n");
}

void show_login_page() {
    print_html_header();
    printf("<html><body>");
    printf("<h1>Login</h1>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
    printf("</body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret123") == 0) {
        print_html_header();
        printf("<html><body>");
        printf("<h1>Secret settings</h1>");
        printf("</body></html>");
    } else {
        show_login_page();
    }
}

int main() {
    char *username = getenv("HTTP_USERNAME");
    char *password = getenv("HTTP_PASSWORD");

    if (username == NULL || password == NULL) {
        show_login_page();
    } else {
        do_login(username, password);
    }

    return 0;
}