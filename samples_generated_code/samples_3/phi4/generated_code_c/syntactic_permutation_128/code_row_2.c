#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find "GET" or end of input
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET", 3) == 0) {
            // Extract username from URL, assuming format: GET /hello/username HTTP/1.1
            char *start = strstr(buffer, "/hello/");
            if (start != NULL) {
                start += strlen("/hello/");
                char *end = strchr(start, ' ');
                if (end != NULL) {
                    size_t username_len = end - start;
                    if (username_len < sizeof(buffer)) {
                        // Write the HTTP response header
                        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
                        
                        // Write the hello message with the extracted username
                        fprintf(response, "Hello %.*s", (int)username_len, start);
                    }
                }
            }
        }
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");  // Simulated request file
    FILE *response = fopen("response.txt", "w"); // Simulated response file
    
    if (request == NULL || response == NULL) {
        return 1; // File open error
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}