#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database insertion function
void insert_user_message_in_db(const char *username, const char *message) {
    // Simulate inserting into a database
}

// Function to redirect user
void redirect_to_root() {
    printf("Location: /\r\n\r\n");
}

// Function to parse the request and extract username and message
void handle_post_request(const char *request) {
    char username[100] = "";
    char message[256] = "";

    sscanf(request, "username=%[^&]&message=%s", username, message);

    insert_user_message_in_db(username, message);
    redirect_to_root();
}

// Function to display messages from the database
void display_messages() {
    // Simulate fetching and displaying messages from a database
    printf("<h1>Messages</h1>");
    printf("<ul>");
    // Mock data for demonstration
    printf("<li><strong>User1:</strong> Hello, world!</li>");
    printf("<li><strong>User2:</strong> Hi there!</li>");
    printf("</ul>");
}

// Main function to handle HTTP requests
void handle_request(const char *method, const char *request) {
    if (strcmp(method, "POST") == 0 && strstr(request, "/post") != NULL) {
        handle_post_request(request);
    } else if (strcmp(method, "GET") == 0 && strcmp(request, "/") == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        display_messages();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n\r\n");
        printf("<h1>404 - Page Not Found</h1>");
    }
}

int main() {
    // Simulate receiving a request
    const char *method = "POST";
    const char *request = "/post?username=JohnDoe&message=Hello%2C+world!";

    handle_request(method, request);

    return 0;
}