#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void render_template(const char *template_name, const char *username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Error opening template file");
        return;
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

void hello(const char *username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    strncpy(username, argv[1], MAX_USERNAME_LENGTH - 1);
    username[MAX_USERNAME_LENGTH - 1] = '\0';

    hello(username);

    return 0;
}