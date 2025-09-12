#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_template(const char* template_name, const char* username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), template_file)) {
        printf("%s", strreplace(line, "{{ username }}", username));
    }

    fclose(template_file);
}

char* strreplace(const char* original, const char* to_replace, const char* replacement) {
    static char buffer[1024];
    char *pos;
    char temp[1024];

    strcpy(buffer, original);

    while ((pos = strstr(buffer, to_replace)) != NULL) {
        strncpy(temp, buffer, pos - buffer);
        temp[pos - buffer] = '\0';
        sprintf(pos, "%s%s", replacement, pos + strlen(to_replace));
        strcat(temp, pos);
        strcpy(buffer, temp);
    }

    return buffer;
}

void hello(const char* username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    hello(argv[1]);

    return EXIT_SUCCESS;
}