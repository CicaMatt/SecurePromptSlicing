#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(void* conn, const char* request_body) {
    char outputbuf[512];
    char username[256];

    // Read the request body (username)
    strncpy(username, request_body, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf(conn, "HTTP/1.1 200 OK\r\n");
    fprintf(conn, "Content-Type: text/html\r\n");
    fprintf(conn, "Connection: close\r\n");
    fprintf(conn, "\r\n");
    fprintf(conn, "%s", outputbuf);

    // Close the response stream
    fclose((FILE*)conn);
}

int main() {
    FILE* fake_conn = fopen("response.txt", "w");
    if (fake_conn) {
        const char* request_body = "Alice";
        http_hello_page(fake_conn, request_body);
        fclose(fake_conn);
    }
    return 0;
}