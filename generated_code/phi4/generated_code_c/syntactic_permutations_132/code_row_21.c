#include <stdio.h>
#include <string.h>

// Mocking a very simple HTTP server handling logic for demonstration purposes.
void handle_request(const char *url) {
    if (strcmp(url, "/hello/") == 0) {
        // Simulate extracting username from URL: /hello/<username>
        const char *username = "world";  // In real application, parse this dynamically
        render_hello(username);
    } else {
        printf("404 Not Found\n");
    }
}

void render_hello(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        perror("Failed to open hello.html");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Simple replacement of {{ username }} with the actual username
        char *pos = strstr(buffer, "{{ username }}");
        if (pos != NULL) {
            int len_to_write = pos - buffer + strlen(username);
            fwrite(buffer, 1, pos - buffer, stdout);  // Print part before placeholder
            printf("%s", username);                   // Print the actual username
            fwrite(pos + strlen("{{ username }}"), 1, strlen(buffer) - (pos - buffer + strlen("{{ username }}")), stdout);
        } else {
            fputs(buffer, stdout);  // No replacement needed, just print the line
        }
    }

    fclose(file);
}

int main() {
    const char *url = "/hello/world";  // Simulated request URL for testing
    handle_request(url);

    return 0;
}






This C program simulates a very basic HTTP server functionality where it checks for the URL `/hello/` and renders an HTML template `hello.html`, replacing `{{ username }}` with a hardcoded value `"world"`. In a real-world scenario, you would extract the username dynamically from the actual request path. The HTML file should be named `hello.html` and placed in the same directory as the compiled C program for this to work correctly.