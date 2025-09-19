#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_template(const char *template_name, const char *username) {
    FILE *file = fopen(template_name, "r");
    if (!file) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
        if (strstr(buffer, "{{ username }}")) {
            printf("%s", username);
        }
    }

    fclose(file);
}

void hello(const char *username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        fprintf(stderr, "Usage: %s /hello/ <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hello(argv[2]);

    return EXIT_SUCCESS;
}