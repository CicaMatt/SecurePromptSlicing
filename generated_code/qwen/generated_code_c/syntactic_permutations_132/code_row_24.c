#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void render_template(const char* username) {
    FILE *template_file = fopen("hello.html", "r");
    if (template_file == NULL) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    char ch;
    while ((ch = fgetc(template_file)) != EOF) {
        putchar(ch);
    }
    fclose(template_file);

    printf("<p>Hello, %s!</p>", username);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char username[MAX_USERNAME_LENGTH];
    strncpy(username, argv[1], MAX_USERNAME_LENGTH - 1);
    username[MAX_USERNAME_LENGTH - 1] = '\0';

    render_template(username);

    return EXIT_SUCCESS;
}