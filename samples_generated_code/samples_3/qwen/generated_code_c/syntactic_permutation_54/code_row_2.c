#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void show_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<form method='post' action='/do_login'>\n");
    printf("Username: <input type='text' name='username'><br>\n");
    printf("Password: <input type='password' name='password'><br>\n");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login() {
    char *username = getenv("HTTP_POST_DATA");
    char *password = strchr(username, '&') + 8;

    username[strcspn(username, "&")] = '\0';

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html>\n");
        printf("<body>\n");
        printf("Invalid username or password.\n");
        printf("</body>\n");
        printf("</html>\n");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        show_login_form();
    } else if (strcmp(request_method, "POST") == 0) {
        do_login();
    }

    return 0;
}