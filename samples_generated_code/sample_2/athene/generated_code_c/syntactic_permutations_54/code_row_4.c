#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<form method='post' action='/do_login'>");
    printf("<label for='username'>Username:</label>");
    printf("<input type='text' id='username' name='username'><br>");
    printf("<label for='password'>Password:</label>");
    printf("<input type='password' id='password' name='password'><br>");
    printf("<input type='submit' value='Login'></form>");
}

void do_login() {
    char username[100], password[100];
    size_t length;
    char *content_length = getenv("CONTENT_LENGTH");
    if (content_length != NULL) {
        length = atoi(content_length);
        if (length > 0 && length < sizeof(username) + sizeof(password)) {
            fread(username, 1, length, stdin);
            username[length] = '\0';
            sscanf(username, "username=%[^&]&password=%s", username, password);

            if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
                printf("Content-Type: text/html\n");
                printf("Location: /admin_page\n\n");
            } else {
                printf("Content-Type: text/html\n\n");
                printf("<h1>Invalid username or password</h1>");
            }
        }
    }
}