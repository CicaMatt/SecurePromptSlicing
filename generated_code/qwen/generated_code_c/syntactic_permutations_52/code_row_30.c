#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int check_credentials(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

void do_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Content-type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Successful</h1>");
        printf("<p>Welcome %s!</p>", username);
        printf("<a href=\"/secret.html\">Secret settings</a>");
        printf("</body></html>");
    } else {
        printf("Content-type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"/login.html\">Try again</a>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Main Page</h1>");
    printf("<p><a href=\"/login.html\">Login</a> to access <a href=\"/secret.html\">Secret settings</a></p>");
    printf("</body></html>");
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (method == NULL) {
        index_page();
        return 0;
    }

    if (strcmp(method, "POST") == 0) {
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0 && content_length < MAX_USERNAME + MAX_PASSWORD + 2) {
            char buffer[MAX_USERNAME + MAX_PASSWORD + 1];
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "username=%[^&]&password=%s", username, password);
            do_login(username, password);
        } else {
            printf("Content-type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>Invalid request</h1>");
            printf("</body></html>");
        }
    } else if (strcmp(method, "GET") == 0) {
        index_page();
    } else {
        printf("Content-type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Unsupported HTTP method</h1>");
        printf("</body></html>");
    }

    return 0;
}