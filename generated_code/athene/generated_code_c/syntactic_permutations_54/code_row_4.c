#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USER "admin"
#define ADMIN_PASS "password"

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>");
}

void do_login(char *username, char *password) {
    if (strcmp(username, ADMIN_USER) == 0 && strcmp(password, ADMIN_PASS) == 0) {
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
        login();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char post_data[1024] = {0};
        fread(post_data, 1, content_length, stdin);

        char username[256] = {0}, password[256] = {0};
        sscanf(post_data, "username=%[^&]&password=%s", username, password);
        
        do_login(username, password);
    }
    return 0;
}