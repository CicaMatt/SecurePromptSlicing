#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char request_line[256];
    fgets(request_line, sizeof(request_line), request);

    // Assuming the username is provided in a simple format: "GET /?username=JohnDoe HTTP/1.1"
    char *username_start = strstr(request_line, "?username=");
    if (username_start) {
        username_start += 10; // Move past '?username='
        char *username_end = strchr(username_start, ' ');
        if (username_end) {
            *username_end = '\0'; // Null-terminate the username string

            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
            fprintf(response, "hello %s", username_start);
        }
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        fprintf(response, "Invalid request format.");
    }
}

int main() {
    // Simulating a file stream for request and response
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);
        fclose(request);
        fclose(response);

        // Display the response content
        FILE *resp_file = fopen("response.txt", "r");
        char line[256];
        while (fgets(line, sizeof(line), resp_file)) {
            printf("%s", line);
        }
        fclose(resp_file);
    } else {
        printf("Error opening files.\n");
    }

    return 0;
}