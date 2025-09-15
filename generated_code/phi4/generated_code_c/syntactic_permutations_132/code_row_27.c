#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

void render_template(const char *template_path, const char *username) {
    FILE *file = fopen(template_path, "r");
    if (!file) {
        perror("Unable to open template file");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);

    printf("\nHello, %s!\n", username);
}

void hello(const char *username) {
    const char *template_path = "hello.html";
    render_template(template_path, username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hello(argv[1]);

    return EXIT_SUCCESS;
}
