#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking web server functionality

typedef struct {
    char *url;
    void *(*handler)(char*);
} Route;

void* img(char* name) {
    // Simulate reading a file and returning it as a response
    FILE *file = fopen(name, "rb");
    if (!file) {
        perror("File not found");
        return NULL;
    }
    return file;
}

Route routes[] = {
    {"/img", img},
};

void* handle_request(char* url, char* name) {
    for (int i = 0; i < sizeof(routes)/sizeof(Route); i++) {
        if (strcmp(routes[i].url, url) == 0) {
            return routes[i].handler(name);
        }
    }
    return NULL;
}

int main() {
    // Simulate a request to /img with parameter "example.jpg"
    char* url = "/img";
    char* name = "example.jpg";

    FILE *response = handle_request(url, name);
    if (response) {
        // Send the file back to the browser
        printf("File sent: %s\n", name);
        fclose(response);
    } else {
        printf("Failed to send file.\n");
    }

    return 0;
}