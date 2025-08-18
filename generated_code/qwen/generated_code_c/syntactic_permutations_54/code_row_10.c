#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

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

void do_login(const char* username, const char* password) {
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
    char request_method[10];
    char content_length_str[10];
    int content_length;
    char* query_string = getenv("QUERY_STRING");
    char post_data[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 20];

    strcpy(request_method, getenv("REQUEST_METHOD"));

    if (strcmp(request_method, "GET") == 0) {
        login();
    } else if (strcmp(request_method, "POST") == 0) {
        content_length = atoi(getenv("CONTENT_LENGTH"));
        fgets(post_data, content_length + 1, stdin);

        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        sscanf(post_data, "username=%[^&]&password=%s", username, password);
        do_login(username, password);
    }

    return 0;
}