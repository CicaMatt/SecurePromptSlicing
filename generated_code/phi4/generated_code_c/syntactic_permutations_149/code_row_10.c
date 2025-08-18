#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup for a basic HTTP server handling request and response (pseudo-code, not full implementation)
typedef struct {
    char *method;
    char *path;
    char *body;
} HttpRequest;

typedef struct {
    int statusCode;
    char *contentType;
    char *body;
} HttpResponse;

// Mock function to insert the user message into a database
void insert_user_message_in_db(const char *message) {
    // Implementation for inserting a message into a database would go here.
    printf("Message inserted: %s\n", message);
}

void display_messages() {
    // Example messages, normally fetched from the database
    const char *messages[] = {"Hello World!", "Hi there!", "Greetings!"};
    size_t numMessages = sizeof(messages) / sizeof(messages[0]);

    for (size_t i = 0; i < numMessages; ++i) {
        printf("%s\n", messages[i]);
    }
}

HttpResponse handle_post_request(const HttpRequest *request) {
    HttpResponse response;
    if (strcmp(request->method, "POST") == 0 && strcmp(request->path, "/post") == 0) {
        insert_user_message_in_db(request->body);
        response.statusCode = 302; // HTTP status code for redirection
        response.contentType = "text/html";
        response.body = "<html><head><meta http-equiv='refresh' content='0;url=/' /></head></html>";
    } else {
        response.statusCode = 404;
        response.contentType = "text/plain";
        response.body = "Not Found";
    }
    return response;
}

HttpResponse handle_get_request(const HttpRequest *request) {
    HttpResponse response;

    if (strcmp(request->method, "GET") == 0 && strcmp(request->path, "/") == 0) {
        response.statusCode = 200; // HTTP status code for OK
        response.contentType = "text/html";
        
        char *body = (char *)malloc(1024);
        snprintf(body, 1024, "<html><head></head><body><h1>Messages:</h1><ul>");

        display_messages();

        strcat(body, "</ul></body></html>");
        response.body = body;
    } else if (strcmp(request->method, "GET") == 0 && strcmp(request->path, "/messages") == 0) {
        response.statusCode = 200; // HTTP status code for OK
        response.contentType = "text/plain";

        char *body = (char *)malloc(1024);
        display_messages();

        strcat(body, "\n");
        response.body = body;
    } else {
        response.statusCode = 404;
        response.contentType = "text/plain";
        response.body = "Not Found";
    }

    return response;
}

void handle_request(const HttpRequest *request) {
    HttpResponse response;

    if (strcmp(request->method, "POST") == 0) {
        response = handle_post_request(request);
    } else if (strcmp(request->method, "GET") == 0) {
        response = handle_get_request(request);
    }

    printf("Status: %d\n", response.statusCode);
    printf("%s: %s\n", response.contentType ? "Content-Type" : "", response.contentType ? response.contentType : "");
    printf("\n%s\n", response.body);

    if (response.body && strcmp(response.body, "<html><head><meta http-equiv='refresh' content='0;url=/' /></head></html>") != 0) {
        free((void *)response.body);
    }
}

int main() {
    // Mock request for POST to /post
    HttpRequest postRequest = {"POST", "/post", "This is a test message."};
    handle_request(&postRequest);

    // Mock request for GET to /
    HttpRequest getRequestHome = {"GET", "/", NULL};
    handle_request(&getRequestHome);

    // Mock request for GET to /messages (display messages)
    HttpRequest getMessagesRequest = {"GET", "/messages", NULL};
    handle_request(&getMessagesRequest);

    return 0;
}