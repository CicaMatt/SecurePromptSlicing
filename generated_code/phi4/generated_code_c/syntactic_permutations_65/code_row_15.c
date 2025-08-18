#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_http_request(const char *request, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Unable to open file %s for writing.\n", filename);
        return;
    }

    // Find the start of the PDF data in the HTTP request
    const char *start_of_data = strstr(request, "\r\n\r\n") + 4;

    if (start_of_data == NULL) {
        printf("Error: No file data found in the request.\n");
        fclose(file);
        return;
    }

    // Write the PDF data to the file
    while (*start_of_data != '\0') {
        if (fwrite(start_of_data, 1, BUFFER_SIZE, file) < BUFFER_SIZE && *start_of_data != '\0') {
            printf("Error: Failed to write all data to file.\n");
        }
        start_of_data += BUFFER_SIZE;
    }

    fclose(file);
    printf("File uploaded successfully.\n");
}

int main() {
    const char *http_request = "POST /upload HTTP/1.1\r\n"
                               "Host: localhost\r\n"
                               "Content-Type: application/pdf\r\n"
                               "Content-Length: 1234\r\n"
                               "\r\n"
                               "%PDF-1.4..."; // Simulated PDF data

    const char *output_filename = "./uploads/uploaded_file.pdf";

    // Ensure the uploads directory exists
    mkdir("./uploads", 0777);

    handle_http_request(http_request, output_filename);

    return 0;
}