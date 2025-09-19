#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Set-Cookie: username=%s; path=/\r\n", username);
        printf("Location: /secret\r\n\r\n");
    } else {
        printf("<html><body>Login Failed. <a href=\"/\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body><h1>Welcome to the Home Page</h1><a href=\"/login\">Login</a></body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Secret settings</body></html>");
}

int main(int argc, char *argv[]) {
    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0) {
        const char *query = getenv("QUERY_STRING");

        if (strstr(query, "login")) {
            index_page();
        } else if (strstr(query, "do_login")) {
            const char *username = strchr(query, '=') + 1;
            const char *password = strchr(username, '&') + strlen("&password=");
            char *end_password = strchr(password, '&');
            if (end_password) *end_password = '\0';
            do_login(username, password);
        } else if (strstr(query, "secret")) {
            secret_page();
        } else {
            index_page();
        }
    }

    return 0;
}