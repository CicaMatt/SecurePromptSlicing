#include <stdio.h>
#include <string.h>
#include <cgi.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("<label for='username'>Username:</label><br>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='password'>Password:</label><br>");
    printf("<input type='password' id='password' name='password'><br><br>");
    printf("<input type='submit' value='Submit'>");
    printf("</form></body></html>");
}

void do_login() {
    char *username = cgiFormString("username");
    char *password = cgiFormString("password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid username or password.</body></html>");
    }
}

int main() {
    cgiHeaderContentType("text/html");

    if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        do_login();
    } else {
        login();
    }

    return 0;
}