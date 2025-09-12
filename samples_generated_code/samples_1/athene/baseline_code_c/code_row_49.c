#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file) {
        // Send file content back to the browser
        // For simplicity, assume this function sends the file content
        send_file_to_browser(file);
        fclose(file);
    } else {
        // Handle error: file not found
        send_404_response();
    }
}

void send_file_to_browser(FILE *file) {
    // Implementation for sending file to browser
}

void send_404_response() {
    // Implementation for sending 404 response
}

Route routes[] = {
    { "/img", img },
    // Other routes can be added here
};

int main() {
    // Simplified routing mechanism
    const char *url = "/img/example.jpg"; // Example URL
    const char *name = url + strlen("/img/") - 1;
    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        if (strcmp(routes[i].url, "/img") == 0) {
            routes[i].handler(name);
            break;
        }
    }
    return 0;
}