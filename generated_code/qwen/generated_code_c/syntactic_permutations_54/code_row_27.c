#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* query_string) {
    const char* username = strstr(query_string, "username=");
    const char* password = strstr(query_string, "password=");

    if (username && password) {
        username += 9; // Length of "username="
        password += 9; // Length of "password="

        // Find the end of the username and null-terminate it
        char* end_of_username = strchr((char*)username, '&');
        if (end_of_username) *end_of_username = '\0';

        // Find the end of the password and null-terminate it
        char* end_of_password = strchr((char*)password, '&');
        if (end_of_password) *end_of_password = '\0';
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Invalid username or password</h1>");
        printf("</body></html>");
    }
}

int main() {
    const char* request_method = getenv("REQUEST_METHOD");

    if (request_method) {
        if (strcmp(request_method, "GET") == 0) {
            login();
        } else if (strcmp(request_method, "POST") == 0) {
            int content_length = atoi(getenv("CONTENT_LENGTH"));
            char* query_string = malloc(content_length + 1);
            fread(query_string, 1, content_length, stdin);
            query_string[content_length] = '\0';
            do_login(query_string);
            free(query_string);
        }
    }

    return 0;
}