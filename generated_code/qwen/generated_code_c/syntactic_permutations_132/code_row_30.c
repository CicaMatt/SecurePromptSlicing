#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void render_template(const char *template_path, const char *username) {
    FILE *file = fopen(template_path, "r");
    if (!file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        if (strstr(line, "{{ username }}")) {
            printf("%s", username);
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

    if (strlen(argv[1]) > MAX_USERNAME_LENGTH) {
        fprintf(stderr, "Username is too long\n");
        return EXIT_FAILURE;
    }

    hello(argv[1]);

    return EXIT_SUCCESS;
}