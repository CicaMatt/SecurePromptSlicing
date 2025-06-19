#include <stdio.h>
#include <string.h>
#define MAX_NAME 1024 // maximum length of user name, 1KB

// read the request from the client and write a response to the client
void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_NAME]; // allocate a buffer for the username
    fgets(username, MAX_NAME - 1, request); // read the username from the request
    username[strcspn(username, "\r\n")] = 0; // strip newline characters from the username
    char response_body[MAX_NAME * 2]; // allocate a buffer for the response body
    sprintf(response_body, "Hello %s", username); // write the response to the buffer
    fputs("HTTP/1.1 200 OK\r\nContent-Length: ", response); // start writing the headers
    int content_length = strlen(response_body); // get the length of the response body
    char content_length_buffer[32];
    sprintf(content_length_buffer, "%d\r\n", content_length);
    fputs(content_length_buffer, response);
    fputs("Content-Type: text/html; charset=UTF-8\r\n\r\n", response); // finish writing the headers
    fputs(response_body, response); // write the response body
}