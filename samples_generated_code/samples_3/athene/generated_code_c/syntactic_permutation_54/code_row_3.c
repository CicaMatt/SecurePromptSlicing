#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password123"

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
    char *method = getenv("REQUEST_METHOD");
    if (method && strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *data = malloc(content_length + 1);
        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        char username[100], password[100];
        sscanf(data, "username=%[^&]&password=%s", username, password);

        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("Location: /admin_page\n");
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<p>Invalid username or password.</p>");
            printf("</body></html>");
        }

        free(data);
    }
}