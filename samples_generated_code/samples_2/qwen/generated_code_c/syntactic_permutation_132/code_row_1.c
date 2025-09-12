#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 256
#define TEMPLATE_PATH "hello.html"

void render_template(const char *username) {
    FILE *template_file = fopen(TEMPLATE_PATH, "r");
    if (!template_file) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof(line), template_file)) {
        printf("%s", line);
        if (strstr(line, "{{ username }}")) {
            printf("%s", username);
        }
    }

    fclose(template_file);
}

void hello(const char *username) {
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    if (strlen(username) > MAX_USERNAME_LENGTH) {
        fprintf(stderr, "Username is too long\n");
        return EXIT_FAILURE;
    }

    hello(username);
    return 0;
}