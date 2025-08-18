#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>Login</title></head>\n");
    printf("<body>\n");
    printf("<h2>Please log in:</h2>\n");
    printf("<form action=\"/do_login\" method=\"POST\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>\n");
    printf("Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    // Simulate reading from POST request (for demonstration purposes)
    if (sscanf(stdin, "%s %s", username, password) == 2) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("Location: /admin_page\n\n");
        } else {
            printf("Content-Type: text/plain\n\n");
            printf("Login failed. Please try again.\n");
        }
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Invalid request format.\n");
    }
}

int main() {
    // Simulate HTTP method and path
    char method[10];
    char path[100];

    fgets(method, sizeof(method), stdin);
    strtok(method, "\r\n");
    fgets(path, sizeof(path), stdin);
    strtok(path, "\r\n");

    if (strcmp(method, "GET") == 0 && strcmp(path, "/login") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && strcmp(path, "/do_login") == 0) {
        do_login();
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found\n");
    }

    return 0;
}