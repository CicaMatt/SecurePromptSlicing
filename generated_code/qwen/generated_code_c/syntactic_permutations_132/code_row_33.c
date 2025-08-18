#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define TEMPLATE_FILE "hello.html"

void render_template(const char *username) {
    FILE *template_file = fopen(TEMPLATE_FILE, "r");
    if (!template_file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), template_file)) {
        char *placeholder = strstr(line, "{{ username }}");
        if (placeholder) {
            int prefix_length = placeholder - line;
            fwrite(line, 1, prefix_length, stdout);
            fputs(username, stdout);
            fwrite(placeholder + strlen("{{ username }}"), 1, strlen(line) - prefix_length - strlen("{{ username }}"), stdout);
        } else {
            fputs(line, stdout);
        }
    }

    fclose(template_file);
}

void hello(const char *username) {
    printf("Content-Type: text/html\n\n");
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char username[MAX_USERNAME_LENGTH + 1];
    strncpy(username, argv[1], MAX_USERNAME_LENGTH);
    username[MAX_USERNAME_LENGTH] = '\0';

    hello(username);

    return EXIT_SUCCESS;
}