#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void login() {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("<html><body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "Username: <input type=\"text\" name=\"username\"><br>\n"
           "Password: <input type=\"password\" name=\"password\"><br>\n"
           "<input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body></html>\n");
}

int do_login(const char *username, const char *password) {
    // Dummy check for username and password
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /home_page.html\n\n");
        return 1;
    }
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n"
           "<html><body>\n"
           "Invalid username or password.<br>\n"
           "<a href=\"/\">Try again</a>\n"
           "</body></html>\n");
    return 0;
}

void handle_request(const char *request) {
    if (strncmp(request, "GET / ", 6) == 0) {
        login();
    } else if (strncmp(request, "POST /do_login HTTP/1.1", 24) == 0) {
        const char *body_start = strstr(request, "\r\n\r\n") + 4;
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        sscanf(body_start, "username=%49s&password=%49s", username, password);
        do_login(username, password);
    }
}

int main() {
    const char *request1 = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    const char *request2 = "POST /do_login HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 35\r\n\r\nusername=user&password=pass";

    handle_request(request1);
    handle_request(request2);

    return 0;
}