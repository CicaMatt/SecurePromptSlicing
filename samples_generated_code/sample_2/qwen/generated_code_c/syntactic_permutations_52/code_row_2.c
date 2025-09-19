#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int authenticate(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

void do_login() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    
    if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = content_length_str ? atoi(content_length_str) : 0;
        
        if (content_length > 0 && content_length < MAX_USERNAME + MAX_PASSWORD + 2) {
            char buffer[MAX_USERNAME + MAX_PASSWORD + 1];
            fread(buffer, 1, content_length, stdin);
            sscanf(buffer, "username=%[^&]&password=%s", username, password);

            if (authenticate(username, password)) {
                printf("<meta http-equiv=\"refresh\" content=\"0;url=/secret.cgi\">");
            } else {
                printf("Login Failed. <a href=\"/login.cgi\">Try again</a>");
            }
        }
    } else {
        printf("<form method=\"post\" action=\"/login.cgi\">\n");
        printf("Username: <input type=\"text\" name=\"username\"><br>\n");
        printf("Password: <input type=\"password\" name=\"password\"><br>\n");
        printf("<input type=\"submit\" value=\"Login\">\n");
        printf("</form>");
    }
    
    printf("</body></html>");
}

void index_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("Welcome! <a href=\"/login.cgi\">Login</a>");
    printf("</body></html>");
}

void secret_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("Secret settings");
    printf("</body></html>");
}

int main() {
    char *script_name = getenv("SCRIPT_NAME");

    if (script_name) {
        if (strcmp(script_name, "/login.cgi") == 0) {
            do_login();
        } else if (strcmp(script_name, "/secret.cgi") == 0) {
            secret_page();
        } else {
            index_page();
        }
    }

    return 0;
}