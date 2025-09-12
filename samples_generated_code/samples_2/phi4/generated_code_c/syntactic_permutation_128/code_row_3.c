#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for reading data from file stream (request)
char* read_request(FILE *request) {
    fseek(request, 0, SEEK_END);
    long length = ftell(request);
    fseek(request, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        return NULL;
    }

    fread(buffer, 1, length, request);
    buffer[length] = '\0';
    return buffer;
}

// Mock function for writing data to file stream (response)
void write_response(FILE *response, const char *data) {
    fprintf(response, "%s", data);
}

void http_hello_page(FILE *request, FILE *response) {
    // Read the request
    char *request_data = read_request(request);
    if (!request_data) {
        return;
    }

    // Extract username from request (assuming it's a simple HTTP GET with "username" query parameter)
    const char *start = strstr(request_data, "username=");
    if (!start || start == request_data) {  // No username or malformed request
        free(request_data);
        write_response(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request");
        return;
    }

    char *end = strchr(start + 9, ' ');  // Find space after the username parameter value
    if (!end) {
        free(request_data);
        write_response(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request");
        return;
    }
    
    size_t username_len = end - (start + 9);
    char *username = malloc(username_len + 1);
    if (!username) {
        free(request_data);
        write_response(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nServer error");
        return;
    }
    
    strncpy(username, start + 9, username_len);
    username[username_len] = '\0';

    // Construct response
    char *response_message = malloc(100 + strlen(username));
    if (!response_message) {
        free(request_data);
        free(username);
        write_response(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nServer error");
        return;
    }
    
    sprintf(response_message, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);

    // Write response
    write_response(response, response_message);
    
    free(request_data);
    free(username);
    free(response_message);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}