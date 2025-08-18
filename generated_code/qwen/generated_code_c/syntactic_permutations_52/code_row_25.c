#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int is_logged_in = 0;
char session_username[MAX_USERNAME_LENGTH];

void do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        strncpy(session_username, username, MAX_USERNAME_LENGTH);
        session_username[MAX_USERNAME_LENGTH - 1] = '\0';
        is_logged_in = 1;
        printf("Location: /home\nContent-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Login Failed</h2>");
        printf("<p>Invalid username or password.</p>");
        printf("<a href=\"/login\">Try again</a>");
        printf("</body></html>");
    }
}

void show_login_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"/do_login\" method=\"post\">");
    printf("<label for=\"username\">Username:</label><br>");
    printf("<input type=\"text\" id=\"username\" name=\"username\"><br>");
    printf("<label for=\"password\">Password:</label><br>");
    printf("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
    printf("<input type=\"submit\" value=\"Submit\">");
    printf("</form>");
    printf("</body></html>");
}

void show_home_page() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    if (is_logged_in) {
        printf("<h2>Welcome, %s</h2>", session_username);
        printf("<a href=\"/secret\">Go to secret settings</a><br>");
    } else {
        printf("<h2>Welcome, Guest</h2>");
        printf("<a href=\"/login\">Login</a>");
    }
    printf("</body></html>");
}

void show_secret_page() {
    if (is_logged_in) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h2>Secret settings</h2>");
        printf("</body></html>");
    } else {
        printf("Location: /login\nContent-Type: text/html\n\n");
    }
}

int main() {
    char* request_method = getenv("REQUEST_METHOD");
    char* query_string = getenv("QUERY_STRING");

    if (strcmp(request_method, "GET") == 0) {
        if (query_string && strcmp(query_string, "/login") == 0) {
            show_login_page();
        } else if (query_string && strcmp(query_string, "/home") == 0) {
            show_home_page();
        } else if (query_string && strcmp(query_string, "/secret") == 0) {
            show_secret_page();
        }
    } else if (strcmp(request_method, "POST") == 0) {
        char buffer[1024];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fgets(buffer, content_length + 1, stdin);

        char* username_start = strstr(buffer, "username=") + strlen("username=");
        char* password_start = strstr(buffer, "password=") + strlen("password=");
        char* end_of_username = strchr(username_start, '&');
        int username_length = end_of_username - username_start;

        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        strncpy(username, username_start, username_length);
        username[username_length] = '\0';

        strcpy(password, password_start);

        do_login(username, password);
    }

    return 0;
}