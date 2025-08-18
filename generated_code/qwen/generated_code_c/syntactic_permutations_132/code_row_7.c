#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_template(const char *template_name, const char *username) {
    FILE *file = fopen(template_name, "r");
    if (!file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Simple replacement of {{ username }} with the actual username
        const char *placeholder = "{{ username }}";
        char *pos = strstr(line, placeholder);
        if (pos) {
            fwrite(line, 1, pos - line, stdout);
            fputs(username, stdout);
            fwrite(pos + strlen(placeholder), 1, strlen(line) - (pos - line) - strlen(placeholder), stdout);
        } else {
            fwrite(line, 1, strlen(line), stdout);
        }
    }

    fclose(file);
}

void hello(const char *username) {
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