#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} User;

void render_template(const char* template_file, const char* username) {
    FILE *file = fopen(template_file, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len; ++i) {
            if (buffer[i] == '{' && buffer[i + 1] == '{') {
                printf("%s", username);
                i += 2;
            } else {
                putchar(buffer[i]);
            }
        }
    }
    fclose(file);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }
    hello(argv[1]);
    return EXIT_SUCCESS;
}