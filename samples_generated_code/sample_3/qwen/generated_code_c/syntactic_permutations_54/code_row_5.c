#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void get_login_form() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form method=\"post\" action=\"/do_login\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(const char* query_string) {
    char username[BUFFER_SIZE] = {0};
    char password[BUFFER_SIZE] = {0};

    sscanf(query_string, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        get_login_form();
    }
}

int main(void) {
    const char* request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL) {
        if (strcmp(request_method, "GET") == 0) {
            get_login_form();
        } else if (strcmp(request_method, "POST") == 0) {
            char buffer[BUFFER_SIZE] = {0};
            fread(buffer, sizeof(char), BUFFER_SIZE - 1, stdin);
            do_login(buffer);
        }
    }

    return 0;
}