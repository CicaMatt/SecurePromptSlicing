#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void render_template(const char *template_name, const char *username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), template_file)) {
        // Simple placeholder replacement
        if (strstr(line, "{{ username }}")) {
            printf("%.*s%s%s\n", (int)(strstr(line, "{{ username }}") - line), line, username, strstr(line, "}}") + 2);
        } else {
            printf("%s", line);
        }
    }

    fclose(template_file);
}

void hello(const char *username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char username[MAX_USERNAME_LENGTH];
    strncpy(username, argv[1], MAX_USERNAME_LENGTH - 1);
    username[MAX_USERNAME_LENGTH - 1] = '\0';

    hello(username);

    return EXIT_SUCCESS;
}