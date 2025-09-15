#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read content from a file into a buffer
char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, file);
    fclose(file);

    string[fsize] = '\0';
    return string;
}

// Function to render the template with the username
char* render_template(const char *template_content, const char *username) {
    size_t buffer_size = strlen(template_content) + strlen(username) + 1;
    char *rendered = malloc(buffer_size);

    snprintf(rendered, buffer_size, "%s%s", template_content, username);
    return rendered;
}

// Function to handle the URL and call the appropriate function
void hello(const char *username) {
    // Read the content of hello.html
    char *template_content = read_file("hello.html");

    // Render the template with the provided username
    char *response = render_template(template_content, username);

    // Output the response
    printf("%s\n", response);

    // Free allocated memory
    free(template_content);
    free(response);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];

    // Simulate visiting the URL /hello/<username>
    hello(username);

    return EXIT_SUCCESS;
}
