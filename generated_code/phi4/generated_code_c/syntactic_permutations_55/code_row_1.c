#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

// Mock functions to simulate HTTP requests and responses
void send_http_response(int status_code, const char *response) {
    printf("HTTP/1.1 %d OK\n", status_code);
    printf("%s\n", response);
}

int get_request_method() {
    // Simulate a GET request method; in real-world use appropriate libraries.
    return 0;
}

char* get_request_url() {
    // Simulate getting URL from an HTTP request
    char *url = "/login";
    return url;
}

void parse_query_string(const char *query, char **username, char **password) {
    *username = NULL;
    *password = NULL;

    const char *param_username = "username=";
    const char *param_password = "password=";

    char *start_username = strstr(query, param_username);
    char *start_password = strstr(query, param_password);

    if (start_username != NULL) {
        start_username += strlen(param_username);
        char *end_username = strchr(start_username, '&');
        if (end_username == NULL) end_username = start_username + strlen(start_username);
        *username = strndup(start_username, end_username - start_username);
    }

    if (start_password != NULL) {
        start_password += strlen(param_password);
        char *end_password = strchr(start_password, '&');
        if (end_password == NULL) end_password = start_password + strlen(start_password);
        *password = strndup(start_password, end_password - start_password);
    }
}

void login() {
    char buffer[MAX_BUFFER];

    // Simulate reading from HTTP request
    fgets(buffer, MAX_BUFFER, stdin);

    if (strstr(buffer, "GET") != NULL) {
        send_http_response(200, "<html><body>Login Page</body></html>");
    } else {
        send_http_response(405, "Method Not Allowed");
    }
}

void do_login() {
    char buffer[MAX_BUFFER];
    
    // Simulate reading from HTTP request
    fgets(buffer, MAX_BUFFER, stdin);

    if (strstr(buffer, "POST") != NULL) {
        char *query = strstr(buffer, "?");
        query += 1;

        char *username;
        char *password;

        parse_query_string(query, &username, &password);

        if (username && password) {
            // Simulate successful login
            send_http_response(200, "<html><body>Welcome, " + username + "</body></html>");
        } else {
            send_http_response(400, "<html><body>Login Failed</body></html>");
        }

        free(username);
        free(password);
    } else {
        send_http_response(405, "Method Not Allowed");
    }
}

void index() {
    char buffer[MAX_BUFFER];

    // Simulate reading from HTTP request
    fgets(buffer, MAX_BUFFER, stdin);

    if (strstr(buffer, "GET") != NULL) {
        send_http_response(200, "<html><body>Index Page</body></html>");
    } else {
        send_http_response(405, "Method Not Allowed");
    }
}

void user_page() {
    char buffer[MAX_BUFFER];

    // Simulate reading from HTTP request
    fgets(buffer, MAX_BUFFER, stdin);

    if (strstr(buffer, "GET") != NULL) {
        send_http_response(200, "<html><body>User Page</body></html>");
    } else {
        send_http_response(405, "Method Not Allowed");
    }
}

void admin_page() {
    char buffer[MAX_BUFFER];

    // Simulate reading from HTTP request
    fgets(buffer, MAX_BUFFER, stdin);

    if (strstr(buffer, "GET") != NULL) {
        send_http_response(200, "<html><body>Admin Page</body></html>");
    } else {
        send_http_response(405, "Method Not Allowed");
    }
}

int main() {
    char *url = get_request_url();

    if (strcmp(url, "/login") == 0) {
        login();
    } else if (strcmp(url, "/do_login") == 0) {
        do_login();
    } else if (strcmp(url, "/index") == 0) {
        index();
    } else if (strcmp(url, "/user_page") == 0) {
        user_page();
    } else if (strcmp(url, "/admin_page") == 0) {
        admin_page();
    } else {
        send_http_response(404, "<html><body>Not Found</body></html>");
    }

    return 0;
}