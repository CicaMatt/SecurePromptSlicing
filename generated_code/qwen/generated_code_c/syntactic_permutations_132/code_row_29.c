#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

void render_template(const char *template_name, const char *username) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "%s.html", template_name);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Failed to open template file");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '$' && (ch = fgetc(file)) == '{' && (ch = fgetc(file)) == 'u') {
            printf("%s", username);
            while ((ch = fgetc(file)) != '}') {
                if (ch == EOF) break;
            }
        } else {
            putchar(ch);
        }
    }

    fclose(file);
}

void hello(const char *username) {
    render_template("hello", username);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hello(argv[1]);

    return EXIT_SUCCESS;
}