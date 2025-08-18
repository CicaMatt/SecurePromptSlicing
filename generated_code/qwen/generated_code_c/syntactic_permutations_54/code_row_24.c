#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "admin"

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(char *data) {
    char username[100] = "";
    char password[100] = "";
    sscanf(data, "username=%99[^&]&password=%99s", username, password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Location: admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Failed</h1>");
        printf("</body></html>");
    }
}

int main() {
    if (getenv("REQUEST_METHOD") != NULL) {
        if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0) {
            login();
        } else if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
            char *data = getenv("CONTENT_LENGTH");
            int length = atoi(data);
            char *body = malloc(length + 1);
            fread(body, 1, length, stdin);
            body[length] = '\0';
            do_login(body);
            free(body);
        }
    }
    return 0;
}