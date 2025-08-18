#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[256] = {0};

    // Read request line by line until the end of headers or an empty line is found
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET ", 4) == 0) {
            char *uri_start = buffer + 4;
            char *end_of_uri = strchr(uri_start, ' ');
            if (end_of_uri != NULL && end_of_uri != uri_start) {
                size_t username_length = end_of_uri - uri_start;
                strncpy(username, uri_start, username_length);
                username[username_length] = '\0';
                
                // Extract the parameter after '?'
                char *param_start = strchr(uri_start, '?');
                if (param_start != NULL && param_start < end_of_uri) {
                    param_start++;
                    size_t name_len = param_start - uri_start - 1;
                    char *eq_pos = memchr(param_start, '=', username_length - name_len);
                    if (eq_pos != NULL && eq_pos < end_of_uri) {
                        char *value_start = eq_pos + 1;
                        size_t value_len = end_of_uri - value_start;
                        strncpy(username, value_start, value_len);
                        username[value_len] = '\0';
                    }
                }

                break;
            }
        } else if (strcmp(buffer, "\r\n") == 0) {
            // Headers have ended
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    }

    return 0;
}