#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void login() {
    printf("Content-type: text/html\n\n");
    printf("<form action=\"/login\" method=\"post\">");
    printf("<label for=\"username\">Username:</label><br>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"password\">Password:</label><br>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
}
void login_post() {
    char* username = getenv("username");
    char* password = getenv("password");

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Content-type: text/html\n\n");
        printf("<p>Login successful</p>");
    } else {
        login();
    }
}
int main() {
    char* request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        login_post();
    }

    return 0;
}