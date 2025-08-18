#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *hello_html_template = 
    "<html><body>"
    "  <h1>Hello, %s!</h1>"
    "</body></html>";

void handle_request(const char *path) {
    if (strncmp(path, "/hello/", 7) == 0) {
        const char *username_start = path + 7;
        size_t username_len = strlen(username_start);
        
        char response[256];
        snprintf(response, sizeof(response), hello_html_template, username_start);

        printf("%s\n", response);
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}