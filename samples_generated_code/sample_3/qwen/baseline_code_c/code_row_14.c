#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
} Session;

Session current_session = {"Guest"};

int check_credentials(const char* username, const char* password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void do_login(const char* username, const char* password) {
    if (check_credentials(username, password)) {
        strncpy(current_session.username, username, MAX_USERNAME);
        printf("Location: secret_page.html\r\n\r\n");
    } else {
        printf("<html><body>Login Failed. <a href='index.html'>Try again</a></body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body><h1>Welcome to the Home Page</h1><a href='login_form.html'>Login</a></body></html>");
}

void secret_page() {
    if (strcmp(current_session.username, "admin") == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Secret settings</body></html>");
    } else {
        printf("Location: index.html\r\n\r\n");
    }
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        char* query_string = getenv("QUERY_STRING");
        if (query_string != NULL && strstr(query_string, "action=index")) {
            index_page();
        } else if (query_string != NULL && strstr(query_string, "action=secret")) {
            secret_page();
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body>Invalid request</body></html>");
        }
    } else if (strcmp(request_method, "POST") == 0) {
        char username[MAX_USERNAME];
        char password[MAX_PASSWORD];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0 && content_length < MAX_USERNAME + MAX_PASSWORD) {
            fgets(username, MAX_USERNAME, stdin);
            fgets(password, MAX_PASSWORD, stdin);
            // Simple parsing assuming input format: username=admin&password=password
            char* username_start = strstr(username, "username=") + strlen("username=");
            char* password_start = strstr(password, "password=") + strlen("password=");
            *strchr(username_start, '&') = '\0';
            do_login(username_start, password_start);
        } else {
            printf("<html><body>Invalid input</body></html>");
        }
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Unsupported request method</body></html>");
    }

    return 0;
}