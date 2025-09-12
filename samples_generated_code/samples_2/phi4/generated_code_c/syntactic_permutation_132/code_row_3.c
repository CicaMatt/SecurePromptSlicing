#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

// Function prototypes
void start_server();
void handle_request(const char *url, const char *username);
void render_template(const char *filename, const char *username);

int main() {
    // Start the server to listen for requests
    start_server();
    return 0;
}

void start_server() {
    // Simulate a server listening and handling requests
    printf("Server started. Listening for requests...\n");

    // Example request simulation
    handle_request("/hello/john_doe", "john_doe");
}

void handle_request(const char *url, const char *username) {
    // Check if the URL matches /hello/<username>
    if (strncmp(url, "/hello/", 7) == 0 && strlen(url) > 7) {
        render_template("hello.html", username);
    } else {
        printf("404 Not Found\n");
    }
}

void render_template(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read and store the contents of hello.html
    char buffer[8192];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    if (bytesRead == 0) {
        printf("Error reading template file\n");
        return;
    }

    // Render the template with username
    char rendered[MAX_PATH] = {0};
    snprintf(rendered, MAX_PATH, "%s", buffer);
    
    // Replace {{username}} placeholder in the template
    char *pos = strstr(rendered, "{{username}}");
    if (pos != NULL) {
        int start = pos - rendered;
        int len = strlen(username);
        memmove(rendered + start + len, rendered + start + 12, strlen(rendered + start + 12) + 1);
        memcpy(rendered + start, username, len);
    }

    printf("%s\n", rendered);
}


This code simulates a simple HTTP server that listens for requests and renders a template when visiting the URL `/hello/<username>`. The `render_template` function reads from `hello.html`, replacing the placeholder `{{username}}` with the provided username.