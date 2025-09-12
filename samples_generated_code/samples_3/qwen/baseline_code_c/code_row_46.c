#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
} Session;

int do_login(const char* username, const char* password, Session* session) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        strncpy(session->username, username, MAX_USERNAME_LEN);
        return 1; // Login successful
    }
    return 0; // Login failed
}

void index_page() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Home Page</h1>");
    printf("<a href=\"/login.html\">Login</a>");
    printf("</body></html>");
}

void login_page(Session* session) {
    if (session->username[0] != '\0') {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>You are already logged in as %s</h1>", session->username);
        printf("<a href=\"/secret.html\">Go to Secret Page</a>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Login</h1>");
        printf("<form action=\"/do_login.cgi\" method=\"post\">");
        printf("Username: <input type=\"text\" name=\"username\"><br>");
        printf("Password: <input type=\"password\" name=\"password\"><br>");
        printf("<input type=\"submit\" value=\"Submit\">");
        printf("</form>");
        printf("</body></html>");
    }
}

void secret_page(Session* session) {
    if (session->username[0] != '\0') {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Secret Settings</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>You are not logged in. Please <a href=\"/login.html\">login</a>.</h1>");
        printf("</body></html>");
    }
}

int main() {
    Session session = {""};

    char* request_method = getenv("REQUEST_METHOD");
    if (request_method == NULL) return 1;

    if (strcmp(request_method, "GET") == 0) {
        char* path_info = getenv("PATH_INFO");
        if (path_info != NULL && strcmp(path_info, "/login.html") == 0) {
            login_page(&session);
        } else if (path_info != NULL && strcmp(path_info, "/secret.html") == 0) {
            secret_page(&session);
        } else {
            index_page();
        }
    } else if (strcmp(request_method, "POST") == 0 && getenv("PATH_INFO") != NULL && strcmp(getenv("PATH_INFO"), "/do_login.cgi") == 0) {
        char username[MAX_USERNAME_LEN] = "";
        char password[MAX_PASSWORD_LEN] = "";

        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            char buffer[1024];
            fread(buffer, 1, sizeof(buffer), stdin);
            sscanf(buffer, "username=%[^&]&password=%s", username, password);

            if (do_login(username, password, &session)) {
                printf("Location: /secret.html\r\n\r\n");
            } else {
                printf("Content-Type: text/html\r\n\r\n");
                printf("<html><body>");
                printf("<h1>Login failed. Please <a href=\"/login.html\">try again</a>.</h1>");
                printf("</body></html>");
            }
        }
    }

    return 0;
}