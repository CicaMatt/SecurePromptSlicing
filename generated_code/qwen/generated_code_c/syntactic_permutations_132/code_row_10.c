#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void read_template(const char *filename, char *buffer) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fread(buffer, sizeof(char), BUFFER_SIZE, file);
    fclose(file);
}

void render_template(const char *template_path, const char *username) {
    char template[BUFFER_SIZE];
    read_template(template_path, template);

    char *username_placeholder = strstr(template, "{{ username }}");
    if (username_placeholder) {
        memmove(username_placeholder + strlen(username), username_placeholder, strlen(username_placeholder) + 1);
        memcpy(username_placeholder, username, strlen(username));
    }

    printf("%s", template);
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