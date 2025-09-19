#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(void *conn) {
    char username[256];
    char outputbuf[512];
    int bytes_read;

    // Read the request body (username)
    bytes_read = fread(username, 1, sizeof(username) - 1, conn);
    if (bytes_read > 0) {
        username[bytes_read] = '\0';
    } else {
        strcpy(username, "Guest");
    }

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf(conn, "HTTP/1.1 200 OK\r\n");
    fprintf(conn, "Content-Type: text/html\r\n");
    fprintf(conn, "Content-Length: %zu\r\n", strlen(outputbuf));
    fprintf(conn, "\r\n"); // End of headers
    fwrite(outputbuf, 1, strlen(outputbuf), conn);

    // Close the response stream
    fclose(conn);
}