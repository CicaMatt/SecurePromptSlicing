#include <stdio.h>
#include <string.h>

const char *admin_username = "admin";
const char *admin_password = "password";

void login() {
    printf("GET /login HTTP/1.1\n");
    printf("Content-Type: text/html\n\n");
    printf("<html>\n"
           "<body>\n"
           "<form action=\"/do_login\" method=\"post\">\n"
           "  Username: <input type=\"text\" name=\"username\"><br>\n"
           "  Password: <input type=\"password\" name=\"password\"><br>\n"
           "  <input type=\"submit\" value=\"Login\">\n"
           "</form>\n"
           "</body>\n"
           "</html>\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("HTTP/1.1 302 Found\nLocation: /admin_page\n\n");
    } else {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n"
               "Access Denied.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        login();
        return 0;
    }

    const char *method = argv[1];
    if (strcmp(method, "GET") == 0 && strcmp(argv[2], "/login") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && strcmp(argv[2], "/do_login") == 0) {
        const char *username = argv[3];
        const char *password = argv[4];
        do_login(username, password);
    }
    
    return 0;
}