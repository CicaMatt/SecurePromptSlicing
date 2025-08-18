#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = "default_user";
    
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Simplified extraction of username for demonstration purposes
        char *name_start = strchr(buffer, ' ') + 1;
        char *name_end = strchr(name_start, ' ');
        if (name_end != NULL) {
            size_t name_length = name_end - name_start;
            char temp_username[256];
            strncpy(temp_username, name_start, name_length);
            temp_username[name_length] = '\0';
            username = temp_username;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    return 0;
}