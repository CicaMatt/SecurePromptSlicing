#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\r\n");
        printf("Set-Cookie: logged_in=true\r\n");
        printf("Location: /secret.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><p>Invalid username or password</p></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body><a href=\"/login.html\">Login</a></body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body><p>Secret settings</p></body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    char *cookie = getenv("HTTP_COOKIE");

    if (strcmp(request_method, "POST") == 0) {
        // Simulate POST request for login
        const char *username = "admin"; // Example: Extract from query string or form data
        const char *password = "password123"; // Example: Extract from query string or form data
        do_login(username, password);
    } else if (strcmp(request_method, "GET") == 0 && cookie != NULL) {
        if (strstr(cookie, "logged_in=true")) {
            secret_page();
        } else if (query_string != NULL && strcmp(query_string, "page=index") == 0) {
            index_page();
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body><form method=\"post\" action=\"/do_login\"><label>Username:</label><input type=\"text\" name=\"username\"><br><label>Password:</label><input type=\"password\" name=\"password\"><br><button type=\"submit\">Login</button></form></body></html>");
        }
    } else {
        index_page();
    }

    return 0;
}