#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void render_template(const char *template_name, const char *username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Failed to open template file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), template_file)) {
        char *pos = strstr(buffer, "{{ username }}");
        if (pos) {
            strncpy(pos, username, MAX_USERNAME_LENGTH);
            pos[MAX_USERNAME_LENGTH] = '\0'; // Ensure null termination
        }
        printf("%s", buffer);
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

    hello(argv[1]);

    return EXIT_SUCCESS;
}