#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login() {
    printf("GET /login HTTP/1.1\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(char* username, char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /admin_page\r\n\r\n");
    } else {
        printf("HTTP/1.1 401 Unauthorized\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Invalid username or password</h1>");
        printf("</body></html>");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        login();
    } else {
        do_login(argv[1], argv[2]);
    }
    return 0;
}