#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>\n");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

void do_login(char *username, char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>\n");
        printf("<h1>Access Denied</h1>\n");
        printf("</body></html>\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        login();
    } else if (strcmp(argv[1], "GET") == 0) {
        login();
    } else if (strcmp(argv[1], "POST") == 0 && argc > 3) {
        do_login(argv[2], argv[3]);
    }
    
    return 0;
}