#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void render_template(const char *template_name, const char *username) {
    FILE *file = fopen(template_name, "r");
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

void handle_hello_request(const char *username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char username[MAX_USERNAME_LENGTH];
    strncpy(username, argv[1], MAX_USERNAME_LENGTH - 1);
    username[MAX_USERNAME_LENGTH - 1] = '\0';

    handle_hello_request(username);

    return EXIT_SUCCESS;
}