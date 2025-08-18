#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void login() {
    printf("GET request received.\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"POST\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login(char *username, char *password) {
    const char admin_username[] = "admin";
    const char admin_password[] = "password123";

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf("Location: /admin_page\n");
        printf("\nRedirecting to admin page...\n");
    } else {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Invalid username or password.</h2>");
        printf("</body></html>");
    }
}

int main() {
    char request_type[10];
    char *username = "admin";
    char *password = "password123";

    // Simulating GET request for login
    strcpy(request_type, "GET");
    if (strcmp(request_type, "GET") == 0) {
        login();
    }
    
    // Simulating POST request to do_login with admin credentials
    strcpy(request_type, "POST");
    if (strcmp(request_type, "POST") == 0) {
        do_login(username, password);
    }

    return 0;
}