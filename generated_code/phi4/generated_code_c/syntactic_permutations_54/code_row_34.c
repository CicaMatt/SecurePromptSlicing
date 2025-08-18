#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n\n");
        return 1;
    }
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<p>Invalid username or password.</p>");
    printf("</body></html>");
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        login();
        return 0;
    }

    if (strcmp(argv[1], "GET") == 0 && strcmp(argv[2], "/login") == 0) {
        login();
    } else if (strcmp(argv[1], "POST") == 0 && strcmp(argv[2], "/do_login") == 0) {
        const char *username = getenv("HTTP_USERNAME");
        const char *password = getenv("HTTP_PASSWORD");

        if (username != NULL && password != NULL) {
            do_login(username, password);
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<p>Username and Password must be provided.</p>");
            printf("</body></html>");
        }
    }

    return 0;
}