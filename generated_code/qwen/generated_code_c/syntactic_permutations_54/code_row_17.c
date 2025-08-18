#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method='post' action='/do_login'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str == NULL) {
        printf("Content-Type: text/plain\n\nMissing CONTENT_LENGTH environment variable.\n");
        return;
    }
    
    int content_length = atoi(content_length_str);
    char buffer[1024];
    if (content_length > sizeof(buffer) - 1) {
        printf("Content-Type: text/plain\n\nInput too large.\n");
        return;
    }

    fread(buffer, 1, content_length, stdin);
    buffer[content_length] = '\0';

    char *username_start = strstr(buffer, "username=");
    char *password_start = strstr(buffer, "&password=");

    if (username_start == NULL || password_start == NULL) {
        printf("Content-Type: text/plain\n\nInvalid input format.\n");
        return;
    }

    username_start += strlen("username=");
    password_start += strlen("&password=");

    char *end_of_username = strchr(username_start, '&');
    if (end_of_username != NULL) {
        *end_of_username = '\0';
    }

    char *end_of_password = strchr(password_start, '&');
    if (end_of_password != NULL) {
        *end_of_password = '\0';
    }

    if (strcmp(username_start, "admin") == 0 && strcmp(password_start, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/plain\n\nLogin failed.\n");
    }
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        do_login();
    } else {
        printf("Content-Type: text/plain\n\nUnsupported request method.\n");
    }

    return 0;
}