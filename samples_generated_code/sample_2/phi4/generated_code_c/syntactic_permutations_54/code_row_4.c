#include <stdio.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "password"

void login() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form>");
    printf("</body></html>");
}

void do_login() {
    char username[50], password[50];

    // Simulate form data
    strcpy(username, "admin");  // Replace with actual input retrieval logic
    strcpy(password, "password");  // Replace with actual input retrieval logic

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Location: /admin_page\n\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    char request_type[10];
    strcpy(request_type, "GET");  // Replace with actual HTTP method detection

    if (strcmp(request_type, "GET") == 0) {
        login();
    } else if (strcmp(request_type, "POST") == 0) {
        do_login();
    }

    return 0;
}