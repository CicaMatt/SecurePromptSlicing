#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256] = {0};
    size_t bytesRead;

    // Read the username from the request body
    if ((bytesRead = fread(username, 1, sizeof(username) - 1, request)) > 0) {
        username[bytesRead] = '\0'; // Null-terminate the string
    }

    // Construct the response HTML page with the given username
    char outputbuf[512];
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fputs("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", response);
    fputs(outputbuf, response);

    // Flush and close the response stream
    fflush(response);
}

int main() {
    FILE *request = tmpfile(); // Simulate request input
    FILE *response = tmpfile(); // Simulate response output

    // Example: writing a username to the request file for demonstration purposes
    const char *test_username = "JohnDoe";
    fputs(test_username, request);
    rewind(request);  // Reset the file position indicator

    // Call the function with simulated input and output files
    http_hello_page(request, response);

    // Read and print the response content from the temporary file
    rewind(response);
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), response) != NULL) {
        printf("%s", buffer);
    }

    fclose(request);
    fclose(response);
    
    return 0;
}