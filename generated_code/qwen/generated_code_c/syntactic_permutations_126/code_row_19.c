#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char *outputbuf, size_t outputbuflen) {
    const char *response = "<html><body><h1>Hello, World!</h1></body></html>";
    strncpy(outputbuf, response, outputbuflen);
    outputbuf[outputbuflen - 1] = '\0'; // Ensure null-termination
}

int main() {
    char request_body[1024]; // Assuming a max request body size of 1024 bytes
    char outputbuf[4096];   // Buffer for the response

    // Simulate reading request body (in a real server, this would be handled by the server framework)
    memset(request_body, 0, sizeof(request_body));
    printf("Enter request body (or press Enter to skip): ");
    fgets(request_body, sizeof(request_body), stdin);

    // Construct the response
    http_hello_page(outputbuf, sizeof(outputbuf));

    // Write the response to the "response stream" (stdout in this example)
    printf("%s", outputbuf);

    // Close the "response stream"
    fflush(stdout);

    return 0;
}