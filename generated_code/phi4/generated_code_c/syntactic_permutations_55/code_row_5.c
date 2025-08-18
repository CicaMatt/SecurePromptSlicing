#include <stdio.h>
#include <string.h>

// Simulate a web server environment

typedef struct {
    char method[6];
    char path[50];
} HttpRequest;

void send_response(const char *response) {
    printf("%s\n", response);
}

int is_login_function(HttpRequest request) {
    return strcmp(request.method, "GET") == 0 && strcmp(request.path, "/login") == 0;
}

int do_login_function(HttpRequest request) {
    return strcmp(request.method, "POST") == 0 && strcmp(request.path, "/do-login") == 0;
}

int index_function(HttpRequest request) {
    return strcmp(request.method, "GET") == 0 && strcmp(request.path, "/index") == 0;
}

int user_page_function(HttpRequest request) {
    return strcmp(request.method, "GET") == 0 && strcmp(request.path, "/user-page") == 0;
}

int admin_page_function(HttpRequest request) {
    return strcmp(request.method, "GET") == 0 && strcmp(request.path, "/admin-page") == 0;
}

void handle_request(HttpRequest request) {
    if (is_login_function(request)) {
        send_response("Login Page");
    } else if (do_login_function(request)) {
        send_response("Processing Login...");
    } else if (index_function(request)) {
        send_response("Index Page");
    } else if (user_page_function(request)) {
        send_response("User Page");
    } else if (admin_page_function(request)) {
        send_response("Admin Page");
    } else {
        send_response("404 Not Found");
    }
}

int main() {
    HttpRequest requests[] = {
        {"GET", "/login"},
        {"POST", "/do-login"},
        {"GET", "/index"},
        {"GET", "/user-page"},
        {"GET", "/admin-page"},
        {"GET", "/unknown"}
    };

    int num_requests = sizeof(requests) / sizeof(HttpRequest);

    for (int i = 0; i < num_requests; ++i) {
        handle_request(requests[i]);
    }

    return 0;
}