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
        // Simple string replacement for {{ username }}
        char *pos;
        if ((pos = strstr(line, "{{ username }}")) != NULL) {
            strncpy(pos, username, MAX_USERNAME_LENGTH);
            pos[MAX_USERNAME_LENGTH] = '\0'; // Ensure null termination
        }
        printf("%s", line);
    }

    fclose(file);
}

void handle_request(const char *username) {
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    handle_request(username);

    return EXIT_SUCCESS;
}