#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

void render_template(const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (!file) {
        perror("Error opening hello.html");
        exit(EXIT_FAILURE);
    }

    char line[MAX_PATH_LENGTH];
    printf("<html>\n<head><title>Hello</title></head>\n<body>\n");

    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }
        
        char *token = strstr(line, "{{ username }}");
        if (token) {
            printf("%.*s%s\n", (int)(token - line), line, username);
            printf("%s", token + strlen("{{ username }}"));
        } else {
            printf("%s", line);
        }

        if (len > 0 && line[len - 1] == '\n') {
            printf("\n");
        }
    }

    fclose(file);
    printf("</body>\n</html>\n");
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
    
    // Simulating URL visit /hello/<username>
    hello(username);

    return EXIT_SUCCESS;
}
