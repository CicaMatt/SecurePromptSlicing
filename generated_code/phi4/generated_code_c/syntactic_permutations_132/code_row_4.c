#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void handle_request(const char *request);
char* render_template(const char *username);

int main() {
    const char *url = "/hello/john";
    
    // Simulate a request to the URL /hello/<username>
    if (strncmp(url, "/hello/", 7) == 0) {
        size_t len = strlen(url) - 7;
        char username[len + 1];
        strncpy(username, url + 7, len);
        username[len] = '\0';
        
        handle_request(username);
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}

void handle_request(const char *username) {
    char *response = render_template(username);
    if (response != NULL) {
        printf("%s", response);
        free(response);
    }
}

char* render_template(const char *username) {
    // Simulate reading from a template file
    const char *template_content = "<html><body>Hello, <b>%s</b>!</body></html>\n";
    
    // Calculate buffer size for the formatted string
    int buffer_size = snprintf(NULL, 0, template_content, username) + 1;
    char *response = (char *)malloc(buffer_size);
    
    if (response == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    
    // Format the response with the username
    snprintf(response, buffer_size, template_content, username);

    return response;
}