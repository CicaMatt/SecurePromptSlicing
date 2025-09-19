#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 1024

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form></body></html>");
}

void do_login() {
    char buffer[MAX_BUFFER];
    fgets(buffer, MAX_BUFFER, stdin); // Read input from POST request body

    char username[50], password[50];

    sscanf(buffer, "username=%[^&]&password=%s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<p>Access denied. Invalid credentials.</p>");
        printf("</body></html>");
    }
}

int main() {
    char method[MAX_BUFFER];
    fgets(method, MAX_BUFFER, stdin);
    
    if (strncmp(method, "GET", 3) == 0) {
        login();
    } else if (strncmp(method, "POST", 4) == 0) {
        do_login();
    }

    return 0;
}