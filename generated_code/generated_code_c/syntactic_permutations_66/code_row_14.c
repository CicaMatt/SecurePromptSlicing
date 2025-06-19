// This program will accept a PDF file as input from the user, save it to the server's local storage, 
// and display a link to download the file on the same page.

#include <stdio.h> // For printf() function
#include <stdlib.h> // For exit() function
#include <string.h> // For strlen() function
#include <unistd.h> // For fork(), execlp(), and other process-related functions
#include <sys/wait.h> // For waitpid() function
#include <fcntl.h> // For open() function
#include <ctype.h> // For isspace() function
#include "http_req.h" // For http_request() function
#include "mime_type.h" // For get_mime_type() function

// Define the maximum file size in bytes that can be uploaded to the server.
#define MAX_FILE_SIZE 1048576 // 1 MB

// Define the path where the PDF files will be saved on the server.
#define UPLOAD_PATH "/var/www/uploads"

int main() {
    // Create a new HTTP request object.
    http_req *request = http_request_new();
    
    // Check if there are any errors with the HTTP request object.
    if (request == NULL) {
        printf("Error: Could not create new HTTP request.\n");
        exit(1);
    }
    
    // Parse the HTTP request header and extract the file name and size from it.
    char *file_name = http_request_get_header(request, "Content-Disposition");
    int file_size = atoi(http_request_get_header(request, "Content-Length"));
    
    // Check if the file name is valid and within the maximum size limit.
    if (file_name == NULL || strlen(file_name) > 256 || file_size > MAX_FILE_SIZE) {
        printf("Error: Invalid file name or size.\n");
        http_request_destroy(request);
        exit(1);
    }
    
    // Create a new buffer to store the PDF file.
    char *buffer = malloc(file_size + 1);
    
    // Check if there was an error allocating memory for the buffer.
    if (buffer == NULL) {
        printf("Error: Could not allocate enough memory.\n");
        http_request_destroy(request);
        exit(1);
    }
    
    // Read the PDF file into the buffer from standard input.
    size_t bytes_read = fread(buffer, 1, file_size, stdin);
    
    // Check if there was an error reading the PDF file.
    if (bytes_read != file_size) {
        printf("Error: Could not read PDF file.\n");
        free(buffer);
        http_request_destroy(request);
        exit(1);
    }
    
    // NULL-terminate the buffer to ensure it is a valid C string.
    buffer[bytes_read] = '\0';
    
    // Open a new file descriptor for writing to the server's local storage.
    int fd = open(UPLOAD_PATH, O_CREAT | O_WRONLY);
    
    // Check if there was an error opening the file descriptor.
    if (fd == -1) {
        printf("Error: Could not open file.\n");
        free(buffer);
        http_request_destroy(request);
        exit(1);
    }
    
    // Write the PDF file to the server's local storage.
    ssize_t bytes_written = write(fd, buffer, bytes_read);
    
    // Check if there was an error writing the PDF file.
    if (bytes_written != bytes_read) {
        printf("Error: Could not write to file.\n");
        close(fd);
        free(buffer);
        http_request_destroy(request);
        exit(1);
    }
    
    // Close the file descriptor.
    close(fd);
    
    // Free the memory allocated for the buffer.
    free(buffer);
    
    // Destroy the HTTP request object.
    http_request_destroy(request);
    
    // Print a success message to standard output.
    printf("File uploaded successfully.\n");
}