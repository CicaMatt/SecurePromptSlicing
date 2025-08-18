#include <stdio.h>
#include <string.h>

// A simple function that mimics rendering a template with a username.
void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }
    
    // Read and display the contents of the template
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    // Close the file
    fclose(file);

    // Display the username at the position where it is expected in the template
    printf("Hello, %s!\n", username);
}

// A function that simulates a URL handler for /hello/<username>
void hello(const char *url) {
    const char *template_file = "hello.html";
    
    // Extract the username from the URL
    char username[256];
    if (sscanf(url, "/hello/%255s", username) == 1) {
        render_template(template_file, username);
    } else {
        printf("Invalid URL format\n");
    }
}

int main() {
    // Simulate visiting a URL with a username
    const char *url = "/hello/Alice";
    hello(url);

    return 0;
}