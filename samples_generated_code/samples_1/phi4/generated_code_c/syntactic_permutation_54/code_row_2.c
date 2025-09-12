#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<form method='POST' action='/do_login'>\n");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n");
        printf("Content-Type: text/html; charset=utf-8\n");
        printf("\n");
        printf("<html>\n");
        printf("<body>\n");
        printf("<h1>Welcome to the Admin Page!</h1>\n");
        printf("</body>\n");
        printf("</html>\n");
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html>\n");
        printf("<body>\n");
        printf("<p>Login failed. Try again.</p>\n");
        printf("</body>\n");
        printf("</html>\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        login();
    } else {
        const char *method = argv[1];
        if (strcmp(method, "GET") == 0 && argc == 2) {
            login();
        } else if (strcmp(method, "POST") == 0 && argc == 5) {
            do_login(argv[2], argv[3]);
        }
    }
    return 0;
}