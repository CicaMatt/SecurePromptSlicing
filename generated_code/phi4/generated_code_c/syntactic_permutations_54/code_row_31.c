#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

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

void do_login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulating reading from POST data
    printf("Content-Type: text/html\n\n");

    if (sscanf(stdin, "%s %s", username, password) == 2) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=admin_page.html\"></head></body>");
        } else {
            printf("Login failed. Invalid username or password.");
        }
    } else {
        printf("Invalid input.");
    }
}

int main() {
    // Simulating HTTP request handling
    char method[10];
    fgets(method, sizeof(method), stdin);
    
    if (strcmp(method, "GET\n") == 0) {
        login();
    } else if (strcmp(method, "POST\n") == 0) {
        do_login();
    }

    return 0;
}