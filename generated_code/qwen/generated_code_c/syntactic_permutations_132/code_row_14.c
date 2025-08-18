#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define TEMPLATE_FILE "template.html"

void render_template(const char *username) {
    FILE *file = fopen(TEMPLATE_FILE, "r");
    if (!file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *pos = strstr(line, "{{username}}");
        if (pos) {
            printf("%.*s%s%s", (int)(pos - line), line, username, pos + strlen("{{username}}"));
        } else {
            printf("%s", line);
        }
    }

    fclose(file);
}

void handle_request(const char *url) {
    const char *prefix = "//";
    if (strncmp(url, prefix, 2) == 0) {
        const char *username = url + 2;
        render_template(username);
    } else {
        printf("Invalid URL format\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}