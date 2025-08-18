#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password123"

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form method='post' action='/do_login'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='password'>Password:</label>");
    printf("<input type='password' id='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
}

void do_login(char *username, char *password) {
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Location: /admin_page\n");
        printf("Content-Type: text/html\n\n");
        printf("<h1>Welcome Admin!</h1>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<p>Invalid username or password.</p>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        fread(buffer, 1, content_length, stdin);
        sscanf(buffer, "username=%[^&]&password=%s", buffer, buffer + strlen(buffer) + 1);
        do_login(buffer, buffer + strlen(buffer) + 1);
    }
    return 0;
}