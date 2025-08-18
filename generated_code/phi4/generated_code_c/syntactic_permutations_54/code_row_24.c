#include <stdio.h>
#include <string.h>

void login() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char username[50], password[50];
    
    // Simulate reading POST data
    printf("Content-Type: text/html\n");
    printf("\n");
    if (scanf("%49s %49s", username, password) == 2) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            // Redirect to admin page
            printf("<html><body>");
            printf("<script>window.location.href='/admin_page';</script>");
            printf("</body></html>");
        } else {
            // Return an error or redirect back
            printf("Access Denied. Please try again.");
        }
    }
}

int main() {
    char method[10];
    
    // Simulate reading the request method
    scanf("%9s", method);
    
    if (strcmp(method, "GET") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0) {
        do_login();
    }
    
    return 0;
}