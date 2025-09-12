#include <stdio.h>
#include <string.h>

// Mock server responses for demonstration purposes
#define SERVER_RESPONSE "Mock response from server"

typedef struct {
    char method[10];
    char path[50];
} Request;

void send_response(const char* message) {
    printf("%s\n", message);
}

// Function to handle GET requests
void handle_get_request(Request request) {
    if (strcmp(request.path, "/login") == 0) {
        login(request);
    } else if (strcmp(request.path, "/index") == 0) {
        index(request);
    } else if (strcmp(request.path, "/user_page") == 0) {
        user_page(request);
    } else if (strcmp(request.path, "/admin_page") == 0) {
        admin_page(request);
    } else {
        send_response("404 Not Found");
    }
}

// Function to handle POST requests
void handle_post_request(Request request) {
    if (strcmp(request.path, "/do_login") == 0) {
        do_login(request);
    } else {
        send_response("405 Method Not Allowed");
    }
}

void login(Request request) {
    if (strcmp(request.method, "GET") != 0) {
        send_response("405 Method Not Allowed");
        return;
    }
    send_response("GET /login: Displaying login page.");
}

void do_login(Request request) {
    if (strcmp(request.method, "POST") != 0) {
        send_response("405 Method Not Allowed");
        return;
    }
    send_response("POST /do_login: Processing login credentials.");
}

void index(Request request) {
    if (strcmp(request.method, "GET") != 0) {
        send_response("405 Method Not Allowed");
        return;
    }
    send_response("GET /index: Displaying homepage.");
}

void user_page(Request request) {
    if (strcmp(request.method, "GET") != 0) {
        send_response("405 Method Not Allowed");
        return;
    }
    send_response("GET /user_page: Displaying user page.");
}

void admin_page(Request request) {
    if (strcmp(request.method, "GET") != 0) {
        send_response("405 Method Not Allowed");
        return;
    }
    send_response("GET /admin_page: Displaying admin page.");
}

int main() {
    Request requests[] = {
        {"GET", "/login"},
        {"POST", "/do_login"},
        {"GET", "/index"},
        {"GET", "/user_page"},
        {"GET", "/admin_page"}
    };

    for (int i = 0; i < sizeof(requests) / sizeof(Request); ++i) {
        if (strcmp(requests[i].method, "GET") == 0) {
            handle_get_request(requests[i]);
        } else if (strcmp(requests[i].method, "POST") == 0) {
            handle_post_request(requests[i]);
        }
    }

    return 0;
}