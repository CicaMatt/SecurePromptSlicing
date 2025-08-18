#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void render_template(const char *template_name, const char *username) {
    FILE *template_file = fopen(template_name, "r");
    if (!template_file) {
        perror("Failed to open template file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), template_file)) {
        char *pos = strstr(buffer, "{{ username }}");
        if (pos) {
            printf("%.*s%s%s", (int)(pos - buffer), buffer, username, pos + strlen("{{ username }}"));
        } else {
            printf("%s", buffer);
        }
    }

    fclose(template_file);
}

void handle_request(const char *url) {
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        char *end = strchr((char*)username, '/');
        if (end) {
            *end = '\0';
        }
        render_template("hello.html", username);
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}