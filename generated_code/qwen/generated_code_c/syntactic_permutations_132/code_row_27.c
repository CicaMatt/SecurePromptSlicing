#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void render_template(const char *template_name, const char *username) {
    FILE *file = fopen(template_name, "r");
    if (!file) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *username = argv[1];
    hello(username);

    return 0;
}