#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_TEMPLATE_CONTENT 1024

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        perror("Unable to open hello.html");
        exit(EXIT_FAILURE);
    }

    char template_content[MAX_TEMPLATE_CONTENT] = {0};
    size_t bytes_read = fread(template_content, 1, sizeof(template_content) - 1, file);
    fclose(file);

    if (bytes_read == 0 || ferror(file)) {
        perror("Error reading hello.html");
        exit(EXIT_FAILURE);
    }

    char output[MAX_TEMPLATE_CONTENT + strlen(username) * 2];
    snprintf(output, sizeof(output), template_content, username);

    printf("%s\n", output);
}

void hello(const char *username) {
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/hello") != 0) {
        fprintf(stderr, "Usage: %s /hello <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hello(argv[2]);

    return EXIT_SUCCESS;
}
