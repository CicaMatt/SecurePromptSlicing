#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock of a simple web framework and HTTP request/response structures
typedef struct {
    char *username;
    char *message;
} HttpRequest;

typedef struct {
    char *status_code;
    char *headers;
    char *body;
} HttpResponse;

typedef void (*RouteHandler)(HttpRequest*, HttpResponse*);

void insert_user_message_in_db(const char* username, const char* message) {
    // Simulate inserting a message into the database
    printf("Inserting into DB: %s -> %s\n", username, message);
}

// Mock function for redirecting user to / route
HttpResponse* redirect_to_root() {
    HttpResponse *response = malloc(sizeof(HttpResponse));
    response->status_code = "302";
    response->headers = "Location: /\r\n";
    response->body = "";
    return response;
}

void post_route_handler(HttpRequest* req, HttpResponse* res) {
    insert_user_message_in_db(req->username, req->message);
    *res = *(redirect_to_root());
}

// Mock function to simulate displaying messages (simplified version)
HttpResponse* display_messages() {
    // Here we would fetch from the database in a real app
    const char* message_html = "<h1>Messages</h1>"
                               "<ul>"
                               "<li>John Doe: Hello, World!</li>"
                               "<li>Jane Smith: C is great!</li>"
                               "</ul>";

    HttpResponse *response = malloc(sizeof(HttpResponse));
    response->status_code = "200";
    response->headers = "Content-Type: text/html\r\n";
    response->body = message_html;
    return response;
}

void register_routes() {
    // Simulate route registration
    HttpRequest req = { .username = "John Doe", .message = "Hello, World!" };
    HttpResponse res;

    post_route_handler(&req, &res);
    
    printf("Response Status: %s\n", res.status_code);
    printf("Response Headers: %s\n", res.headers);
    if (strcmp(res.body, "") != 0) {
        printf("Response Body:\n%s\n", res.body);
    }

    // Display messages
    HttpResponse *display_res = display_messages();
    printf("Display Messages Status: %s\n", display_res->status_code);
    printf("Display Messages Headers: %s\n", display_res->headers);
    printf("Display Messages Body:\n%s\n", display_res->body);

    free(display_res);
}

int main() {
    register_routes();
    return 0;
}