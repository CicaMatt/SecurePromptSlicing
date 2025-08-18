#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_hello_request(const char *request_body, char *outputbuf) {
    const char *username = request_body;
    snprintf(outputbuf, BUFFER_SIZE,
             "<html><body>Hello, %s! Welcome to our server.</body></html>", username);
}

int main() {
    FILE *response_stream = stdout; // Simulating response stream
    char input_buffer[BUFFER_SIZE] = "JohnDoe"; // Example request body (username)
    char output_buffer[BUFFER_SIZE];

    handle_hello_request(input_buffer, output_buffer);

    fprintf(response_stream, "%s", output_buffer);
    fflush(response_stream);
    fclose(response_stream); // Close the simulated response stream

    return 0;
}