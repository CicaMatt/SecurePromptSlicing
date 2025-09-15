#include <stdio.h>
#include <string.h>

void render_template(const char* username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Replace placeholder with actual username
        if (strstr(buffer, "{{username}}")) {
            fprintf(stdout, "%s", buffer);
            size_t len = strlen(buffer) - 2; // Exclude newline and null terminator
            char *start = strstr(buffer, "{{username}}") + strlen("{{username}}");
            int padding = start - buffer;
            printf("%*.*s%s\n", padding, padding, "", username);
        } else {
            fputs(buffer, stdout);
        }
    }

    fclose(file);
}

void hello(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username_start = url + 7;
        render_template(username_start);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a user visiting the URL
    hello("/hello/Alice");

    return 0;
}
