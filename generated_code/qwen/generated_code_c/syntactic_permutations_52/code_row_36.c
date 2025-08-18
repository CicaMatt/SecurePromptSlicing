#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

void do_login(const char *username, const char *password, Session *session) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        strncpy(session->username, username, MAX_USERNAME_LEN);
        printf("Location: /secret.html\r\n\r\n");
    } else {
        printf("<html><body>Login Failed. <a href='/index.html'>Try again</a></body></html>");
    }
}

void index_page() {
    printf("<html><body>Welcome! <a href='/login.html'>Login</a></body></html>");
}

void secret_page(Session *session) {
    if (strlen(session->username) > 0) {
        printf("<html><body>Secret Page. Welcome, %s!</body></html>", session->username);
    } else {
        printf("Location: /index.html\r\n\r\n");
    }
}

int main() {
    Session session = {""};
    char *request_uri = getenv("REQUEST_URI");
    char *query_string = getenv("QUERY_STRING");

    if (request_uri == NULL) {
        index_page();
    } else if (strcmp(request_uri, "/index.html") == 0) {
        index_page();
    } else if (strcmp(request_uri, "/login.html") == 0 && query_string != NULL) {
        char username[MAX_USERNAME_LEN] = "";
        char password[MAX_PASSWORD_LEN] = "";
        sscanf(query_string, "username=%50[^&]&password=%50s", username, password);
        do_login(username, password, &session);
    } else if (strcmp(request_uri, "/secret.html") == 0) {
        secret_page(&session);
    } else {
        printf("<html><body>404 Not Found</body></html>");
    }
    return 0;
}