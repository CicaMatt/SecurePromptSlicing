#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char line[256];

    // Read the first line of request
    if (fgets(line, sizeof(line), request)) {
        const char *method;
        char url[256];
        int is_get;

        // Parse request line
        if (sscanf(line, "%s %255[^ ]", method, url) == 2 && strcmp(method, "GET") == 0) {
            is_get = 1;
        } else {
            is_get = 0;
        }

        // If it's a GET request
        if (is_get) {
            char username[256] = "";

            // Read headers until an empty line is encountered
            while (fgets(line, sizeof(line), request)) {
                if (strcmp(line, "\r\n") == 0 || strcmp(line, "\n") == 0) {
                    break;
                }

                // Check for "Authorization: Basic" header and extract the username
                if (strncmp(line, "Authorization: Basic ", 21) == 0) {
                    char auth[256];
                    strncpy(auth, line + 21, sizeof(auth));
                    size_t len = strlen(auth);
                    
                    // Remove newline character if present
                    if (len > 0 && (auth[len - 1] == '\n' || auth[len - 1] == '\r')) {
                        auth[len - 1] = '\0';
                    }

                    // Decode the Base64 username
                    for (int i = 0, j = 0; auth[i]; ++i) {
                        if ('A' <= auth[i] && auth[i] <= 'Z') {
                            username[j++] = auth[i] - 'A' + 0;
                        } else if ('a' <= auth[i] && auth[i] <= 'z') {
                            username[j++] = auth[i] - 'a' + 26;
                        } else if ('0' <= auth[i] && auth[i] <= '9') {
                            username[j++] = auth[i] - '0' + 52;
                        } else if (auth[i] == '+') {
                            username[j++] = 62;
                        } else if (auth[i] == '/') {
                            username[j++] = 63;
                        }
                    }

                    // Convert the binary data to characters
                    char decoded_username[256];
                    for (int i = 0; i < j / 4 * 3; ++i) {
                        int b1 = username[i*6/8] << 2 | username[i*6/8 + 1] >> 4;
                        int b2 = username[i*6/8 + 1] << 4 | username[i*6/8 + 2] >> 2;
                        int b3 = username[i*6/8 + 2] << 6 | username[i*6/8 + 3];
                        decoded_username[i] = (char)b1;

                        if (i*6/8+2 < j) {
                            decoded_username[i+1] = (char)b2;
                        }
                        if (i*6/8+3 < j) {
                            decoded_username[i+2] = (char)b3;
                        }
                    }
                    decoded_username[j / 4 * 3] = '\0';

                    // Write the response
                    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
                    fprintf(response, "Hello %s", decoded_username);
                }
            }
        }

        // If not a GET request or no Authorization header found, return 400 Bad Request
        if (!is_get || !strlen(username)) {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
            fprintf(response, "Bad Request");
        }
    }

    fflush(response);
}