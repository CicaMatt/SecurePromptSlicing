#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");

    // Simulate reading the request header to extract username
    fgets(buffer, sizeof(buffer), request); // Read a line (e.g., GET / HTTP/1.1)
    while (!feof(request) && !strchr(buffer, '\n')) {
        strcat(buffer, " ");
        fgets(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), request);
    }

    const char *username_start = strstr(buffer, "username=");
    if (username_start) {
        username_start += 9; // Move past 'username='
        char *username_end = strchr(username_start, '&');
        if (!username_end) username_end = username_start + strlen(username_start);

        size_t username_length = username_end - username_start;
        char username[256];
        strncpy(username, username_start, username_length);
        username[username_length] = '\0';

        fprintf(response, "Hello %s\n", username);
    } else {
        fprintf(response, "Hello guest\n");
    }
}

int main() {
    // Simulating request and response streams
    FILE *request_stream = fmemopen("GET /?username=JohnDoe HTTP/1.1\r\nHost: example.com\r\n\r\n", 60, "r");
    FILE *response_stream = tmpfile();

    http_hello_page(request_stream, response_stream);

    // Rewind the response stream to read and print the output
    rewind(response_stream);
    char response_buffer[512];
    while (fgets(response_buffer, sizeof(response_buffer), response_stream) != NULL) {
        printf("%s", response_buffer);
    }

    fclose(request_stream);
    fclose(response_stream);

    return 0;
}