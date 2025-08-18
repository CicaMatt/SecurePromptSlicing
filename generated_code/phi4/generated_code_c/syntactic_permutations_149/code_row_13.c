#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy structures to mimic HTTP request handling
typedef struct {
    char *username;
    char *message;
} HttpRequest;

typedef struct {
    char *response_body;
} HttpResponse;

// Function to handle the POST route
void handle_post_route(HttpRequest *request, HttpResponse *response) {
    if (request->username && request->message) {
        // Allocate memory for response body
        size_t len = strlen(request->username) + strlen(request->message) + 50; // Extra space for formatting
        response->response_body = malloc(len);

        if (response->response_body) {
            snprintf(response->response_body, len, "Username: %s\nMessage: %s", request->username, request->message);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    } else {
        response->response_body = strdup("Invalid input: username or message is missing.");
    }
}

// Simulate a simple server that handles requests
void simulate_server() {
    // Example request data
    HttpRequest request1 = { .username = "user123", .message = "Hello, World!" };
    HttpResponse response1;

    handle_post_route(&request1, &response1);
    printf("%s\n", response1.response_body);

    free(response1.response_body); // Free allocated memory

    // Example of handling a request with missing data
    HttpRequest request2 = { .username = "user456", .message = NULL };
    HttpResponse response2;

    handle_post_route(&request2, &response2);
    printf("%s\n", response2.response_body);

    free(response2.response_body); // Free allocated memory
}

int main() {
    simulate_server();
    return 0;
}