#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(char *query_string) {
    char username[256] = "";
    char password[256] = "";

    sscanf(query_string, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("Invalid username or password.");
        printf("</body></html>");
    }
}

int main(void) {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *query_string = malloc(content_length + 1);
        fread(query_string, 1, content_length, stdin);
        query_string[content_length] = '\0';
        do_login(query_string);
        free(query_string);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("Invalid request method.");
        printf("</body></html>");
    }

    return 0;
}