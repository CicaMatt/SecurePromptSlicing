#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 100

void render_template(const char *username) {
    FILE *template_file = fopen("hello.html", "r");
    if (template_file == NULL) {
        perror("Failed to open template file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), template_file)) {
        char *pos = strstr(buffer, "{{ username }}");
        if (pos != NULL) {
            strncpy(pos, username, strlen(username));
            pos[strlen(username)] = '\0';
        }
        printf("%s", buffer);
    }

    fclose(template_file);
}

void hello(const char *username) {
    render_template(username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    if (strlen(username) > MAX_USERNAME_LEN) {
        fprintf(stderr, "Username is too long\n");
        return EXIT_FAILURE;
    }

    hello(username);

    return EXIT_SUCCESS;
}