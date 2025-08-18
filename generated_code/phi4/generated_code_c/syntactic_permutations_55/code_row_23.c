#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

typedef struct {
    char username[50];
    char password[50];
} User;

User currentUser = {"", ""};

void handle_http_request(const char *request) {
    if (strncmp(request, "GET /login ", 11) == 0) {
        login();
    } else if (strncmp(request, "POST /do_login ", 15) == 0) {
        do_login(request);
    } else if (strncmp(request, "GET /index ", 10) == 0) {
        index();
    } else if (strncmp(request, "GET /user_page ", 14) == 0) {
        user_page();
    } else if (strncmp(request, "GET /admin_page ", 15) == 0) {
        admin_page();
    }
}

void login() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<form action='/do_login' method='POST'>");
    printf("Username: <input type='text' name='username'><br>");
    printf("Password: <input type='password' name='password'><br>");
    printf("<input type='submit' value='Login'>");
    printf("</form></body></html>\n");
}

void do_login(const char *request) {
    char buffer[MAX_BUFFER];
    strncpy(buffer, request + 15, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *username_token = strstr(buffer, "username=");
    char *password_token = strstr(buffer, "password=");

    if (username_token && password_token) {
        username_token += strlen("username=");
        password_token += strlen("password=");

        char *end_of_username = strchr(username_token, '&');
        if (!end_of_username) end_of_username = buffer + sizeof(buffer) - 1;
        strncpy(currentUser.username, username_token, end_of_username - username_token);
        currentUser.username[end_of_username - username_token] = '\0';

        char *end_of_password = strchr(password_token, ' ');
        if (!end_of_password) end_of_password = buffer + sizeof(buffer) - 1;
        strncpy(currentUser.password, password_token, end_of_password - password_token);
        currentUser.password[end_of_password - password_token] = '\0';
    }

    if (strcmp(currentUser.username, "admin") == 0 && strcmp(currentUser.password, "password123") == 0) {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Location: /admin_page\r\n\r\n");
    } else if (currentUser.username[0] != '\0') { // Assume any non-empty username and password is a valid user
        printf("HTTP/1.1 200 OK\r\n");
        printf("Location: /user_page\r\n\r\n");
    } else {
        printf("HTTP/1.1 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("Invalid credentials. <a href='/login'>Login again</a>");
        printf("</body></html>\n");
    }
}

void index() {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>Welcome to the Index Page</h1>");
    printf("<a href='/login'>Login</a>");
    printf("</body></html>\n");
}

void user_page() {
    if (currentUser.username[0] == '\0') {
        printf("HTTP/1.1 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("Unauthorized access. <a href='/login'>Login</a>");
        printf("</body></html>\n");
    } else {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Welcome, %s!</h1>", currentUser.username);
        printf("<a href='/login'>Logout</a>");
        printf("</body></html>\n");
    }
}

void admin_page() {
    if (strcmp(currentUser.username, "admin") != 0) {
        printf("HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("Forbidden access. <a href='/login'>Login</a>");
        printf("</body></html>\n");
    } else {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Welcome, Admin!</h1>");
        printf("<a href='/login'>Logout</a>");
        printf("</body></html>\n");
    }
}

int main() {
    char request[MAX_BUFFER];

    // Simulating HTTP requests
    strcpy(request, "GET /login ");
    handle_http_request(request);

    strcpy(request, "POST /do_login username=admin&password=password123 ");
    handle_http_request(request);

    strcpy(request, "GET /index ");
    handle_http_request(request);

    strcpy(request, "GET /user_page ");
    handle_http_request(request);

    strcpy(request, "GET /admin_page ");
    handle_http_request(request);

    return 0;
}