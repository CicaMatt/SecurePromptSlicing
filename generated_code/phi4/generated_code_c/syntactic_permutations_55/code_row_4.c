#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256

// Mock functions to represent HTTP requests and responses
void send_http_response(const char *response) {
    printf("%s\n", response);
}

int get_request_parameter(const char *param_name, const char *request, char *buffer, size_t buffer_size) {
    // Simulate extracting parameter from GET request URL
    char param_template[64];
    snprintf(param_template, sizeof(param_template), "%s=", param_name);

    if (strstr(request, param_template)) {
        const char *param_value = strstr(request, param_template) + strlen(param_template);
        char *end_param = strchr(param_value, '&');
        if (!end_param)
            end_param = request + strlen(request);
        size_t len = end_param - param_value;
        if (len < buffer_size)
            strncpy(buffer, param_value, len);
        buffer[len] = '\0';
        return 1; // Parameter found
    }
    return 0; // Parameter not found
}

void login_function(const char *request) {
    send_http_response("HTTP/1.1 200 OK\nContent-Type: text/html\n\nLogin Page");
}

int do_login_function(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        send_http_response("HTTP/1.1 200 OK\nContent-Type: text/html\n\nLogin Successful");
        return 1; // Login successful
    } else {
        send_http_response("HTTP/1.1 401 Unauthorized\nContent-Type: text/html\n\nInvalid credentials");
        return 0; // Login failed
    }
}

void index_function(const char *request) {
    send_http_response("HTTP/1.1 200 OK\nContent-Type: text/html\n\nWelcome to the Homepage");
}

void user_page_function(const char *request) {
    send_http_response("HTTP/1.1 200 OK\nContent-Type: text/html\n\nUser Page");
}

void admin_page_function(const char *request) {
    send_http_response("HTTP/1.1 200 OK\nContent-Type: text/html\n\nAdmin Page");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <function_name> [parameters]\n", argv[0]);
        return 1;
    }

    const char *function_name = argv[1];

    if (strcmp(function_name, "login") == 0) {
        login_function(NULL);
    } else if (strcmp(function_name, "do_login") == 0) {
        if (argc < 4) {
            printf("Usage: %s do_login <username> <password>\n", argv[0]);
            return 1;
        }
        const char *username = argv[2];
        const char *password = argv[3];
        do_login_function(username, password);
    } else if (strcmp(function_name, "index") == 0) {
        index_function(NULL);
    } else if (strcmp(function_name, "user_page") == 0) {
        user_page_function(NULL);
    } else if (strcmp(function_name, "admin_page") == 0) {
        admin_page_function(NULL);
    } else {
        printf("Unknown function: %s\n", function_name);
        return 1;
    }

    return 0;
}