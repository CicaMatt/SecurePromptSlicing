#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype declarations
void handle_request(const char* url);
void render_template(const char* username);

int main() {
    // Simulating a request to /hello/<username>
    const char *url = "/hello/john";
    handle_request(url);
    return 0;
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        size_t username_len = strlen(url + 7);
        char *username = malloc(username_len + 1);
        if (!username) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        strncpy(username, url + 7, username_len);
        username[username_len] = '\0';

        render_template(username);

        free(username);
    } else {
        printf("404 Not Found\n");
    }
}

void render_template(const char *username) {
    const char *template_content =
        "<html><body>"
        "<h1>Hello, %s!</h1>"
        "</body></html>";

    char rendered[512];
    snprintf(rendered, sizeof(rendered), template_content, username);

    printf("%s\n", rendered);
}