#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype for rendering the template
void render_template(const char *username);

// Decorator function that binds a function to a URL pattern
void bind_function_to_url(const char *url_pattern) {
    printf("URL Pattern: %s\n", url_pattern);
    // Simulating user visiting /hello/<username>
    const char *username = "JohnDoe";
    render_template(username);
}

// Function to render the template with username
void render_template(const char *username) {
    printf("Rendering template for user: %s\n", username);

    // Simulate reading from a file (hello.html)
    const char *template_content = "<html><body>Hello, <b>%s</b>!</body></html>";

    // Prepare the output with the username
    char output[256];
    snprintf(output, sizeof(output), template_content, username);

    // Print the rendered content
    printf("%s\n", output);
}

int main() {
    // Simulate binding and visiting URL
    const char *url = "/hello/<username>";
    bind_function_to_url(url);

    return 0;
}