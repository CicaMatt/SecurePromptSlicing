#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESPONSE_SIZE 1024

void send_response(const char *status, const char *message) {
    printf("HTTP/1.1 %s\r\n", status);
    printf("Content-Type: text/plain\r\n");
    printf("\r\n%s\n", message);
}

void login_function(char *request) {
    if (strstr(request, "GET /login") != NULL) {
        send_response("200 OK", "Login page");
    } else {
        send_response("404 Not Found", "Resource not found");
    }
}

void do_login_function(char *request_body) {
    char username[50] = {0};
    char password[50] = {0};

    sscanf(request_body, "username=%49[^&]&password=%49s", username, password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        send_response("200 OK", "Login successful");
    } else {
        send_response("401 Unauthorized", "Invalid credentials");
    }
}

void index_function(char *request) {
    if (strstr(request, "GET /index") != NULL) {
        send_response("200 OK", "Index page content");
    } else {
        send_response("404 Not Found", "Resource not found");
    }
}

void user_profile_function(char *request) {
    if (strstr(request, "GET /user/profile") != NULL) {
        send_response("200 OK", "User profile content");
    } else {
        send_response("404 Not Found", "Resource not found");
    }
}

void admin_page_function(char *request) {
    if (strstr(request, "GET /admin/page") != NULL) {
        send_response("200 OK", "Admin page content");
    } else {
        send_response("404 Not Found", "Resource not found");
    }
}

int main() {
    char request[RESPONSE_SIZE];
    char request_body[RESPONSE_SIZE];

    // Simulating a GET request to /login
    strcpy(request, "GET /login HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n");
    login_function(request);

    // Simulating a POST request to do_login with body data
    strcpy(request_body, "username=admin&password=password123");
    do_login_function(request_body);

    // Simulating a GET request to /index
    strcpy(request, "GET /index HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n");
    index_function(request);

    // Simulating a GET request to user profile
    strcpy(request, "GET /user/profile HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n");
    user_profile_function(request);

    // Simulating a GET request to admin page
    strcpy(request, "GET /admin/page HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n");
    admin_page_function(request);

    return 0;
}