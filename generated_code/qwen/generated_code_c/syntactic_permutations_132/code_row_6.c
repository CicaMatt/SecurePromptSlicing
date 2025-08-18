#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void render_template(const char *template_name, const char *username) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "%s", template_name);
    
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", strreplace(line, "{{ username }}", username));
    }
    fclose(file);
}

char* strreplace(char *orig, const char *rep, const char *with) {
    static char buffer[1024];
    char *p = orig;
    int i = 0;

    while (*p) {
        if (strncmp(p, rep, strlen(rep)) == 0) {
            strcpy(&buffer[i], with);
            i += strlen(with);
            p += strlen(rep);
        } else {
            buffer[i++] = *p++;
        }
    }
    buffer[i] = '\0';
    return buffer;
}

void hello(const char *username) {
    render_template("hello.html", username);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    hello(argv[1]);

    return 0;
}