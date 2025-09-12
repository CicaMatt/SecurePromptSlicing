#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define TEMPLATE_PATH "hello.html"

void render_template(const char *template_path, const char *username) {
    FILE *template_file = fopen(template_path, "r");
    if (!template_file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), template_file)) {
        char *pos = strstr(line, "{{ username }}");
        if (pos) {
            printf("%.*s%s%s", (int)(pos - line), line, username, pos + strlen("{{ username }}"));
        } else {
            printf("%s", line);
        }
    }

    fclose(template_file);
}

void hello(const char *username) {
    render_template(TEMPLATE_PATH, username);
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