#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define TEMPLATE_FILE "template.html"

void render_template(const char *username) {
    FILE *file = fopen(TEMPLATE_FILE, "r");
    if (!file) {
        perror("Failed to open template file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        if (strstr(line, "{{username}}")) {
            printf("%s", username);
        }
    }

    fclose(file);
}

void bind_url(const char *url) {
    char username[MAX_USERNAME_LENGTH + 1];
    if (sscanf(url, "//%50[^\n]", username) == 1) {
        render_template(username);
    } else {
        printf("Invalid URL format\n");
    }
}

int main() {
    const char *url = "//exampleUser";
    bind_url(url);
    return 0;
}