#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define TEMPLATE_PATH "hello.html"

void render_template(const char *username) {
    FILE *template_file = fopen(TEMPLATE_PATH, "r");
    if (!template_file) {
        perror("Failed to open template file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), template_file)) {
        char *placeholder = strstr(buffer, "{{ username }}");
        if (placeholder) {
            size_t prefix_len = placeholder - buffer;
            fwrite(buffer, 1, prefix_len, stdout);
            printf("%s", username);
            fputs(placeholder + strlen("{{ username }}"), stdout);
        } else {
            fputs(buffer, stdout);
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

    char username[MAX_USERNAME_LENGTH + 1];
    strncpy(username, argv[1], MAX_USERNAME_LENGTH);
    username[MAX_USERNAME_LENGTH] = '\0';

    hello(username);

    return EXIT_SUCCESS;
}