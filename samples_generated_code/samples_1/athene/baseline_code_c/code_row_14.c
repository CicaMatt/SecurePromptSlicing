#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

typedef struct {
    char *username;
} Session;

Session session = {NULL};

void do_login(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        session.username = strdup(username);
        printf("Location: /secret.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head>");
        printf("<body onLoad=\"window.location.href='/secret.html'\"></body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login Failed. <a href=\"/login.html\">Try again</a>.</body></html>");
    }
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Welcome! <a href=\"/login.html\">Login here</a>.</body></html>");
}

void secret_page() {
    if (session.username != NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Secret settings. Logged in as %s.</body></html>", session.username);
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head>");
        printf("<body onLoad=\"window.location.href='/login.html'\"></body></html>");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    char *path_info = getenv("PATH_INFO");

    if (strcmp(request_method, "POST") == 0 && path_info != NULL && strcmp(path_info, "/do_login") == 0) {
        char username[100], password[100];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), 99, stdin);
        fgets(password, 100, stdin);
        username[strcspn(username, "&")] = '\0';
        sscanf(strchr(username, '=') + 1, "%[^&]", username);
        sscanf(strchr(password, '=') + 1, "%s", password);
        do_login(username, password);
    } else if (strcmp(path_info, "/") == 0) {
        index_page();
    } else if (strcmp(path_info, "/secret.html") == 0) {
        secret_page();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Page not found.</body></html>");
    }

    return 0;
}