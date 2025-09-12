#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define TEMPLATE_FILE "template.html"

void render_template(const char *username) {
    FILE *file = fopen(TEMPLATE_FILE, "r");
    if (!file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *pos = strstr(line, "{{ username }}");
        if (pos) {
            printf("%.*s%s%s", (int)(pos - line), line, username, pos + strlen("{{ username }}"));
        } else {
            printf("%s", line);
        }
    }

    fclose(file);
}

void handle_user(const char *username) {
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strlen(argv[1]) > MAX_USERNAME_LENGTH) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_user(argv[1]);

    return EXIT_SUCCESS;
}