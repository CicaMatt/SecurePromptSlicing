#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int is_admin(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0;
}

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

void do_login(const char *query_string) {
    char username[MAX_USERNAME] = "";
    char password[MAX_PASSWORD] = "";
    
    if (sscanf(query_string, "username=%[^&]&password=%s", username, password) != 2) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Invalid input.</p>");
        printf("</body></html>");
        return;
    }

    if (is_admin(username, password)) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Login failed. Please try again.</p>");
        printf("</body></html>");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (method == NULL) {
        return 1;
    }

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        char *query_string = malloc(256);
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fgets(query_string, content_length + 1, stdin);
        do_login(query_string);
        free(query_string);
    }

    return 0;
}