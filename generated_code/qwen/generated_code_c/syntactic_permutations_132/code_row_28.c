#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_template(const char *template_name, const char *username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Error opening template file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), template_file)) {
        char *pos = strstr(buffer, "{{ username }}");
        if (pos) {
            printf("%.*s%s%s", (int)(pos - buffer), buffer, username, pos + strlen("{{ username }}"));
        } else {
            printf("%s", buffer);
        }
    }

    fclose(template_file);
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