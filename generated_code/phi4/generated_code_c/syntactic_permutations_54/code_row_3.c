#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "Username: <input type=\"text\" name=\"username\"><br>"
           "Password: <input type=\"password\" name=\"password\"><br>"
           "<input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\nContent-Length: 0\nConnection: close\n");
    } else {
        printf("Login failed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    const char *method = argv[1];
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && argc >= 4) {
        do_login(argv[2], argv[3]);
    } else {
        printf("Invalid request.\n");
    }

    return 0;
}