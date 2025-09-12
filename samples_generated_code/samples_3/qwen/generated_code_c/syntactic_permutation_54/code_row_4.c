#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "admin"

void login() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /admin_page\r\n");
        printf("\r\n");
    } else {
        printf("HTTP/1.1 401 Unauthorized\r\n");
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>Unauthorized</h1>");
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