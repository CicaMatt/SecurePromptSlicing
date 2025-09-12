#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void render_template(const char *template_content, const char *username) {
    printf("%s", template_content);
    size_t len = strlen(template_content);
    for (size_t i = 0; i < len; ++i) {
        if (template_content[i] == '{{' && strncmp(&template_content[i], "{{ username }}", 13) == 0) {
            printf("%s", username);
            i += 12;
        }
    }
}

void hello(const char *username) {
    char buffer[BUFFER_SIZE];
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE - 1, file);
    if (bytes_read == 0 && ferror(file)) {
        perror("Error reading template file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    buffer[bytes_read] = '\0';
    fclose(file);

    render_template(buffer, username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hello(argv[1]);
    return EXIT_SUCCESS;
}