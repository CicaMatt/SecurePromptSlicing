#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME_MAX_LEN 50

void render_template(const char* template_name, const char* username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), template_file)) {
        printf("%s", line);
        if (strstr(line, "{{ username }}")) {
            printf("%s\n", username);
        }
    }

    fclose(template_file);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char username[USERNAME_MAX_LEN + 1];
    strncpy(username, argv[1], USERNAME_MAX_LEN);
    username[USERNAME_MAX_LEN] = '\0';

    hello(username);

    return EXIT_SUCCESS;
}