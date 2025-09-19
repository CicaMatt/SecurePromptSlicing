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
        char *pos = strstr(line, "{{username}}");
        if (pos) {
            strncpy(pos, username, strlen(username));
        }
        printf("%s", line);
    }

    fclose(file);
}

void bind_url(const char *url) {
    char username[MAX_USERNAME_LENGTH];
    sscanf(url, "//%50s", username);
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    bind_url(argv[1]);

    return EXIT_SUCCESS;
}