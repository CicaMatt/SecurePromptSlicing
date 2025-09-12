#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login() {
    printf("GET /login HTTP/1.1\r\n");
    printf("\r\n");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
}

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("HTTP/1.1 302 Found\r\nLocation: /admin_page\r\n\r\n");
    } else {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nLogin failed.");
    }
}

int main() {
    // Simulate a GET request to login
    printf("Simulating GET request to /login:\n");
    login();

    printf("\nSimulating POST request to /do_login with username=admin and password=admin:\n");
    do_login("admin", "admin");

    printf("\nSimulating POST request to /do_login with username=user and password=pass:\n");
    do_login("user", "pass");

    return 0;
}