#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<head><title>Login</title></head>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "Username: <input type=\"text\" name=\"username\"><br>\n"
           "Password: <input type=\"password\" name=\"password\"><br>\n"
           "<input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login(char *data) {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    // Extract username and password from POST data
    sscanf(data, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Location: /admin\n\n");
    } else {
        printf("Content-Type: text/plain\n\n"
               "Access Denied.\n");
    }
}

int main() {
    char method[10];
    char path[BUFFER_SIZE];

    // Simulating an HTTP request
    fgets(method, sizeof(method), stdin);
    fgets(path, sizeof(path), stdin);

    if (strcmp(method, "GET ") == 0 && strcmp(path, "/login\n") == 0) {
        login();
    } else if (strcmp(method, "POST /do_login") == 0) {
        char data[BUFFER_SIZE];
        while (fgets(data, sizeof(data), stdin)) {
            do_login(data);
            break;
        }
    }

    return 0;
}