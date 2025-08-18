#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void render_template(const char *username) {
    FILE *template_file = fopen("template.html", "r");
    if (!template_file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), template_file)) {
        char *pos = strstr(line, "{{ username }}");
        if (pos) {
            fprintf(stdout, "%.*s%s%s", (int)(pos - line), line, username, pos + strlen("{{ username }}"));
        } else {
            fputs(line, stdout);
        }
    }

    fclose(template_file);
}

void handle_request(const char *username) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n");
    printf("\r\n");

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

    handle_request(username);

    return EXIT_SUCCESS;
}