#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

typedef struct {
    const char *username;
} Request;

void render_template(const char *username) {
    FILE *file = fopen("template.html", "r");
    if (!file) {
        printf("Error opening template file.\n");
        return;
    }

    char buffer[MAX_BUFFER];
    while (fgets(buffer, MAX_BUFFER, file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0'; // Remove newline character
        }
        printf("%s\n", buffer);

        if (strstr(buffer, "{{username}}") != NULL) {
            printf("Username: %s\n", username);
        }
    }

    fclose(file);
}

void handle_request(const char *url_path) {
    const char *username = url_path + 1; // Skip the leading '/'
    render_template(username);
}

int main() {
    // Simulate a user visiting the URL "/john_doe"
    handle_request("/john_doe");
    
    return 0;
}
