#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<p>Login failed. Please try again.</p>\n");
        printf("</body></html>\n");
    }
}

int main() {
    const char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        char buffer[BUFFER_SIZE];
        char *data = fgets(buffer, BUFFER_SIZE, stdin);

        if (data != NULL) {
            char username[50], password[50];
            sscanf(data, "username=%[^&]&password=%s", username, password);
            do_login(username, password);
        }
    }

    return 0;
}