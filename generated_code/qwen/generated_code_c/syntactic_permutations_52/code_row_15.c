#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

Session session;

int check_credentials(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

void do_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        strncpy(session.username, username, MAX_USERNAME_LEN);
        printf("Location: secret_page.html\r\n\r\n");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Invalid username or password. <a href='index.html'>Try again</a></p>");
        printf("</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<p>Please <a href='login.html'>Login</a> to access secret settings.</p>");
    printf("</body></html>");
}

void secret_page() {
    if (strlen(session.username) > 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret Settings</h1>");
        printf("<p>Welcome, %s!</p>", session.username);
        printf("</body></html>");
    } else {
        printf("Location: index.html\r\n\r\n");
    }
}

int main() {
    char request_method[50];
    char query_string[256];

    strcpy(session.username, "");

    if (getenv("REQUEST_METHOD") != NULL) {
        strcpy(request_method, getenv("REQUEST_METHOD"));
    }

    if (getenv("QUERY_STRING") != NULL) {
        strcpy(query_string, getenv("QUERY_STRING"));
    }

    if (strcmp(request_method, "GET") == 0 && strstr(query_string, "login=")) {
        char username[MAX_USERNAME_LEN];
        char password[MAX_PASSWORD_LEN];

        sscanf(query_string, "login=%[^&]&password=%s", username, password);
        do_login(username, password);
    } else if (strstr(query_string, "page=secret")) {
        secret_page();
    } else {
        index_page();
    }

    return 0;
}