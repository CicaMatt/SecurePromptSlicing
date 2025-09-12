#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* query_string) {
    char username[MAX_USERNAME_LEN + 1] = {0};
    char password[MAX_PASSWORD_LEN + 1] = {0};

    const char* token = strtok((char*)query_string, "&");
    while (token != NULL) {
        if (strncmp(token, "username=", 9) == 0) {
            strncpy(username, token + 9, MAX_USERNAME_LEN);
        } else if (strncmp(token, "password=", 9) == 0) {
            strncpy(password, token + 9, MAX_PASSWORD_LEN);
        }
        token = strtok(NULL, "&");
    }

    // Check for admin credentials
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("</body></html>");
    }
}

int main() {
    const char* request_method = getenv("REQUEST_METHOD");

    if (request_method == NULL) {
        return 1;
    }

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char* query_string = malloc(content_length + 1);
        if (query_string != NULL && fread(query_string, 1, content_length, stdin) == content_length) {
            query_string[content_length] = '\0';
            do_login(query_string);
        }
        free(query_string);
    }

    return 0;
}