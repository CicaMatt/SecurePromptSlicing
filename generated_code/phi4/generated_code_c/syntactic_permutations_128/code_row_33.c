#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    
    // Read the request line
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find where the method ends and start of URI begins
        char *method_end = strchr(buffer, ' ');
        if (method_end) {
            char *uri_start = method_end + 1;
            
            // Move to the next space for end of URI
            char *uri_end = strchr(uri_start, ' ');
            if (uri_end) {
                int uri_length = uri_end - uri_start;
                
                // Extract the requested resource/URI
                char *requested_uri = malloc(uri_length + 1);
                strncpy(requested_uri, uri_start, uri_length);
                requested_uri[uri_length] = '\0';
                
                // Construct response
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n"); // End of headers
                
                if (strncmp(requested_uri, "/", 1) == 0) {
                    fprintf(response, "hello []\n");
                } else {
                    fprintf(response, "hello [%s]\n", requested_uri + 1);
                }
                
                free(requested_uri);
            }
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) return 1;
    
    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}