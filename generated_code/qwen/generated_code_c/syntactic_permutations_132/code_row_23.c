#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void render_template(const char *template_name, const char *username) {
    FILE *file = fopen(template_name, "r");
    if (!file) {
        perror("Failed to open template file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        char *pos = strstr(buffer, "{{ username }}");
        if (pos) {
            strncpy(pos, username, strlen(username));
            pos[strlen(username)] = '\0';
            printf("%s%s", buffer, pos + strlen("{{ username }}"));
        } else {
            printf("%s", buffer);
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

    const char *username = argv[1];
    if (strlen(username) > MAX_USERNAME_LENGTH) {
        fprintf(stderr, "Username too long\n");
        return EXIT_FAILURE;
    }

    hello(username);

    return EXIT_SUCCESS;
}