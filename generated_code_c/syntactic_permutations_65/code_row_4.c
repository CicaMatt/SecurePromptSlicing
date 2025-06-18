#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

// Define a structure to store information about the uploaded file
struct upload_file_t {
    char *name; // file name
    char *type; // file type
    char *data; // file data
};

// Define an enum to represent the different possible HTTP methods
enum http_method {
    HTTP_GET,
    HTTP_POST
};

// Define a structure to store information about the HTTP request
struct http_request_t {
    enum http_method method; // HTTP method
    char *resource; // resource name
    struct upload_file_t file; // uploaded file
};

// Define an error message for when there is no file data present in the request
static const char* ERROR_NO_FILE = "No file data found.";

// Define a function to create a new upload file structure and return a pointer to it
struct upload_file_t *create_upload_file() {
    struct upload_file_t *file = malloc(sizeof(struct upload_file_t));
    memset(file, 0, sizeof(struct upload_file_t));
    file->name = NULL;
    file->type = NULL;
    file->data = NULL;
    return file;
}

// Define a function to free an upload file structure and the data within it
void free_upload_file(struct upload_file_t *file) {
    if (file != NULL) {
        if (file->name != NULL) free(file->name);
        if (file->type != NULL) free(file->type);
        if (file->data != NULL) free(file->data);
        free(file);
    }
}

// Define a function to create a new HTTP request structure and return a pointer to it
struct http_request_t *create_http_request() {
    struct http_request_t *req = malloc(sizeof(struct http_request_t));
    memset(req, 0, sizeof(struct http_request_t));
    req->method = HTTP_GET;
    req->resource = NULL;
    req->file = create_upload_file();
    return req;
}

// Define a function to free an HTTP request structure and the data within it
void free_http_request(struct http_request_t *req) {
    if (req != NULL) {
        if (req->resource != NULL) free(req->resource);
        free_upload_file(req->file);
        free(req);
    }
}

// Define a function to extract the uploaded file from the HTTP request body and return it as an upload file structure
struct upload_file_t *extract_file_from_request(const char *body) {
    // Find the first newline character in the request body
    const char *newline = strchr(body, '\n');
    
    // If there is no newline, return an error message
    if (newline == NULL) {
        struct upload_file_t *file = create_upload_file();
        file->data = ERROR_NO_FILE;
        return file;
    }
    
    // Allocate a new string for the file name and type
    char *name_and_type = malloc(newline - body + 1);
    memcpy(name_and_type, body, newline - body);
    name_and_type[newline - body] = '\0';
    
    // Split the file name and type on the semicolon character
    char *name = strtok(name_and_type, ";");
    char *type = strtok(NULL, ";");
    
    // Allocate a new string for the file data
    const char *data_start = newline + 1;
    size_t data_length = strlen(body) - (data_start - body);
    char *data = malloc(data_length + 1);
    memcpy(data, data_start, data_length);
    data[data_length] = '\0';
    
    // Create a new upload file structure and return it
    struct upload_file_t *file = create_upload_file();
    file->name = name;
    file->type = type;
    file->data = data;
    return file;
}

// Define a function to handle an HTTP request and return a response message as a string
char *handle_http_request(struct http_request_t *req) {
    // If the HTTP method is GET, return an error message
    if (req->method == HTTP_GET) {
        char *message = "HTTP 405 Method Not Allowed\n";
        return message;
    }
    
    // Extract the uploaded file from the request body
    struct upload_file_t *file = extract_file_from_request(req->body);
    
    // If there was no file data, return an error message
    if (strcmp(file->data, ERROR_NO_FILE) == 0) {
        char *message = "HTTP 400 Bad Request\n";
        free_upload_file(file);
        return message;
    }
    
    // Create a new folder called uploads if it doesn't already exist
    struct stat st = {0};
    if (stat("./uploads", &st) == -1) {
        mkdir("./uploads", 0700);
    }
    
    // Write the uploaded file to a new file in the uploads folder
    char *filepath = malloc(strlen("./uploads/") + strlen(file->name) + 1);
    sprintf(filepath, "./uploads/%s", file->name);
    FILE *f = fopen(filepath, "w");
    if (f == NULL) {
        char *message = "HTTP 500 Internal Server Error\n";
        free_upload_file(file);
        return message;
    }
    fwrite(file->data, sizeof(char), strlen(file->data), f);
    fclose(f);
    
    // Return a success message
    char *message = "HTTP 201 Created\n";
    free_upload_file(file);
    return message;
}

// Define the main function to handle incoming HTTP requests and send responses back to the client
int main(void) {
    // Create a new socket and bind it to port 8080
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    bind(sock, (struct sockaddr *)&server, sizeof(server));
    
    // Listen for incoming connections and accept them
    listen(sock, 3);
    int client = accept(sock, NULL, NULL);
    
    // Receive the HTTP request from the client and store it in a buffer
    char *buffer = malloc(4096);
    recv(client, buffer, 4096, 0);
    
    // Parse the HTTP request into an HTTP request structure
    struct http_request_t *req = create_http_request();
    req->body = buffer;
    
    // Handle the HTTP request and get a response message as a string
    char *message = handle_http_request(req);
    
    // Send the response message back to the client
    send(client, message, strlen(message), 0);
    
    // Close the socket and free any allocated memory
    close(sock);
    free_http_request(req);
    return 0;
}