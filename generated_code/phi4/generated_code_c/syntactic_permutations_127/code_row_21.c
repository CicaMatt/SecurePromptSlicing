#include <stdio.h>
#include <string.h>

typedef struct {
    char *headers;
    char *body;
} Request;

typedef struct {
    FILE *file_stream;
} Response;

void http_hello_page(Request *request, Response *response) {
    // Extract the username from the request body assuming it's in format "username=<username>"
    const char *prefix = "username=";
    char *start = strstr(request->body, prefix);
    
    if (start) {
        start += strlen(prefix);  // Move to the beginning of the username
        size_t username_len = strcspn(start, "\r\n");  // Get length until newline or carriage return
        
        // Allocate memory for the username
        char *username = malloc(username_len + 1);
        if (username) {
            strncpy(username, start, username_len);
            username[username_len] = '\0';  // Null-terminate the string
            
            // Construct the response message
            char response_message[256];
            snprintf(response_message, sizeof(response_message), "Hello %s", username);

            // Write the response to the file stream
            fprintf(response->file_stream, "%s\r\n", response_message);
            
            free(username);  // Free allocated memory for the username
        }
    }
}

int main() {
    // Example request and response
    char example_request_body[] = "username=JohnDoe";
    Request request;
    request.headers = NULL;
    request.body = example_request_body;

    FILE *response_file_stream = stdout;  // For demonstration, use standard output as the file stream
    Response response;
    response.file_stream = response_file_stream;

    http_hello_page(&request, &response);

    return 0;
}