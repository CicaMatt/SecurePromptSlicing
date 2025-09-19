#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("</body></html>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "GET") == 0) {
        get_login_form();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char input[1024];
        fread(input, 1, content_length, stdin);
        char *username = strstr(input, "username=");
        char *password = strstr(input, "&password=");
        if (username && password) {
            username += strlen("username=");
            *strchr(username, '&') = '\0';
            password += strlen("&password=");
            do_login(username, password);
        }
    }
    return 0;
}