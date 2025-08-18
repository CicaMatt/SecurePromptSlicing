#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void do_login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/html\n");
        printf("Set-Cookie: username=%s; Path=/\n", username);
        printf("Location: /secret.html\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid credentials. <a href=\"/login.html\">Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome! <a href=\"/login.html\">Login</a></body></html>");
}

void secret_page(char *username) {
    printf("Content-Type: text/html\n\n");
    if (strcmp(username, USERNAME) == 0) {
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("<html><body>You are not authorized to view this page. <a href=\"/login.html\">Login</a></body></html>");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *query_string = getenv("QUERY_STRING");
    char username[100] = "";
    char password[100] = "";

    if (strcmp(request_method, "POST") == 0 && query_string) {
        sscanf(query_string, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strcmp(request_method, "GET") == 0 && query_string) {
        sscanf(query_string, "username=%s", username);
        secret_page(username);
    } else {
        index_page();
    }

    return 0;
}