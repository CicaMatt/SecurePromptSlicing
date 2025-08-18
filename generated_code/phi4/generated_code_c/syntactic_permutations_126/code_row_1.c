#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    FILE* input_stream;
    FILE* output_stream;
} connection_t;

void http_hello_page(connection_t conn) {
    char username[256];
    
    // Read the request body (username)
    if (fgets(username, sizeof(username), conn.input_stream) != NULL) {
        // Remove newline character from username
        username[strcspn(username, "\r\n")] = 0;
        
        // Construct response body (HTML page)
        char outputbuf[1024];
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><head><title>Hello Page</title></head>"
                 "<body><h1>Hello, %s!</h1></body></html>", username);
        
        // Write the response body to the response stream
        fprintf(conn.output_stream, "HTTP/1.1 200 OK\r\n"
                                   "Content-Type: text/html; charset=UTF-8\r\n"
                                   "Connection: close\r\n"
                                   "\r\n");
        fputs(outputbuf, conn.output_stream);
    }
}

int main() {
    // Simulated input and output streams
    connection_t conn;
    
    FILE* input = tmpfile();
    FILE* output = tmpfile();
    
    fprintf(input, "username=JohnDoe\r\n");  // Simulating a request body with username
    
    fseek(input, 0, SEEK_SET);  // Reset file pointer to the beginning

    conn.input_stream = input;
    conn.output_stream = output;

    http_hello_page(conn);

    fclose(conn.input_stream);
    fclose(conn.output_stream);

    return 0;
}