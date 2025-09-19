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

    char line[256];
    while (fgets(line, sizeof(line), template_file)) {
        char *placeholder = strstr(line, "{{ username }}");
        if (placeholder) {
            *placeholder = '\0'; // Null-terminate the string at the placeholder
            printf("%s%s%s", line, username, placeholder + strlen("{{ username }}"));
        } else {
            printf("%s", line);
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
        fprintf(stderr, "Username too long\n");
        return EXIT_FAILURE;
    }

    hello(username);
    return EXIT_SUCCESS;
}