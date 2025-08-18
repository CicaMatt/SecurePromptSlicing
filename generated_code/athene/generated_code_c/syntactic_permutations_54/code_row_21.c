#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='post'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login() {
    char *content_type = getenv("CONTENT_TYPE");
    if (content_type == NULL || strcmp(content_type, "application/x-www-form-urlencoded") != 0) {
        return;
    }

    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char input[1024] = "";
    fread(input, 1, content_length, stdin);

    char *username = strstr(input, "username=");
    if (username == NULL) return;
    username += 9; // Length of "username="
    char *password = strstr(username, "&password=");
    if (password == NULL) return;
    *password = '\0';
    password += 10; // Length of "&password="

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Content-Type: text/html\n");
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid username or password</body></html>");
    }
}