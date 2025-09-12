#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void login() {
    printf("GET /login HTTP/1.1\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void do_login() {
    char input[256];
    
    printf("POST /do_login HTTP/1.1\r\n");
    printf("Content-Type: application/x-www-form-urlencoded\r\n");
    printf("\r\n");
    
    // Simulate reading POST data from stdin
    fgets(input, sizeof(input), stdin);
    
    // Extract username and password from input
    char *username = strtok(input, "&");
    char *password = strtok(NULL, "&");

    if (username && password) {
        username += strlen("username=");  // Move pointer to start of the actual value
        password += strlen("password=");

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            printf("HTTP/1.1 302 Found\r\n");
            printf("Location: /admin_page\r\n");
            printf("\r\n");
        } else {
            printf("Login failed.\n");
        }
    } else {
        printf("Invalid input format.\n");
    }
}

int main() {
    char request[256];
    
    // Simulate receiving a request
    fgets(request, sizeof(request), stdin);
    
    if (strncmp(request, "GET /login", 10) == 0) {
        login();
    } else if (strncmp(request, "POST /do_login", 15) == 0) {
        do_login();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("\r\n");
    }
    
    return 0;
}