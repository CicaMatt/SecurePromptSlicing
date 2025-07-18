// Importing required dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining struct for storing PDF files
typedef struct pdf_file {
    char *name;
    char *data;
} pdf_file;

// Function to read pdf file and store it in a structure
pdf_file* read_pdf(char *filename) {
    // Open the file in binary mode
    FILE *file = fopen(filename, "rb");
    
    // Check if file exists
    if (file == NULL) {
        printf("Error opening PDF file\n");
        return NULL;
    }
    
    // Get the size of the file
    int size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    
    // Allocate memory for the file data
    pdf_file *pdf = (pdf_file *)malloc(sizeof(pdf_file) + size);
    pdf->name = strdup(filename);
    pdf->data = malloc(size);
    
    // Read the file contents into memory
    int read_bytes = fread(pdf->data, 1, size, file);
    if (read_bytes != size) {
        printf("Error reading PDF file\n");
        return NULL;
    }
    
    // Close the file and return the pdf structure
    fclose(file);
    return pdf;
}

// Function to upload pdf file to web server
int upload_pdf(pdf_file *pdf) {
    // Define a variable for storing HTTP request data
    char http_request[1024];
    
    // Set the HTTP request method and path
    strcpy(http_request, "POST /uploads/");
    strcat(http_request, pdf->name);
    strcat(http_request, " HTTP/1.1\r\nHost: localhost\r\nContent-Length: ");
    
    // Set the content length to the size of the PDF file
    char size[10];
    sprintf(size, "%d", pdf->data_size);
    strcat(http_request, size);
    
    // Set the HTTP request headers
    strcat(http_request, "\r\nContent-Type: application/pdf\r\nConnection: close\r\n\r\n");
    
    // Send the HTTP request to the web server
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *host;
    host = gethostbyname("localhost");
    if (!host) {
        printf("Error getting host information\n");
        return 1;
    }
    
    // Set the server address and port
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);
    memcpy(&serv_addr.sin_addr.s_addr, host->h_addr, host->h_length);
    
    // Connect to the web server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error connecting to web server\n");
        return 1;
    }
    
    // Send the HTTP request and PDF file data
    send(sock, http_request, strlen(http_request), 0);
    send(sock, pdf->data, pdf->data_size, 0);
    
    // Close the socket and return success
    close(sock);
    return 0;
}

// Driver function to test the code
int main() {
    // Read a PDF file from disk
    pdf_file *pdf = read_pdf("test.pdf");
    if (pdf == NULL) {
        printf("Error reading PDF file\n");
        return 1;
    }
    
    // Upload the PDF file to the web server
    int result = upload_pdf(pdf);
    if (result != 0) {
        printf("Error uploading PDF file\n");
        return 1;
    }
    
    // Free memory and exit
    free(pdf->name);
    free(pdf->data);
    free(pdf);
    return 0;
}