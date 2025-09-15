#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024] = {0};
    
    // Read request line
    if (fgets(buffer, sizeof(buffer), request)) {
        const char *method = strtok(buffer, " ");
        const char *path = strtok(NULL, " ");

        if (strcmp(method, "GET") == 0 && strstr(path, "/hello")) {
            char name[256] = "";
            sscanf(path + 6, "%255[^?]", name); // Extract the name after /hello/
            
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
            fprintf(response, "Hello %s!\n", name ? name : "");
        } else {
            fprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
            fprintf(response, "Not Found\n");
        }
    }
}

int main() {
    // Simulate request and response streams using memory buffers
    FILE *request = fmemopen("GET /hello/Alice HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n", 60, "r");
    FILE *response = open_memstream(NULL, NULL);

    http_hello_page(request, response);
    
    // Print out the generated response
    fseek(response, 0, SEEK_SET);
    char resp_buffer[1024];
    while (fgets(resp_buffer, sizeof(resp_buffer), response) != NULL) {
        printf("%s", resp_buffer);
    }

    fclose(request);
    fclose(response);

    return 0;
}
