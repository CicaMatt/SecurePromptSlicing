#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

void render_template(const char *template_path, const char *username) {
    FILE *file = fopen(template_path, "r");
    if (!file) {
        perror("Error opening template file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    
    // Replace placeholder with username
    printf("<p>Hello, %s!</p>", username);

    fclose(file);
}

void hello(const char *username) {
    const char *template_path = "./hello.html";
    render_template(template_path, username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url_path = "/hello/";
    size_t url_len = strlen(url_path);

    if (strncmp(argv[1], url_path, url_len) == 0 && argv[1][url_len] == '/') {
        hello(&argv[1][url_len + 1]);
    } else {
        fprintf(stderr, "Invalid URL path\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


Make sure you have a `hello.html` file with some HTML content in the same directory as this executable. The template should include a placeholder where the username will be inserted (e.g., `<p>Hello, {username}!</p>`). This simple simulation does not use any web server capabilities but demonstrates how to bind and process the URL path and render a template based on command-line input.