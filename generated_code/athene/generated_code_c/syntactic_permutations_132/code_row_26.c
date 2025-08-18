#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 100

typedef struct {
    char *username;
} RequestContext;

void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        size_t pos = 0;
        while ((pos = strcspn(line + pos, "{{username}}")) != 0) {
            printf("%.*s", (int)pos, line);
            if (line[pos] == '{' && line[pos+1] == '{') {
                printf("%s", username);
                pos += strlen("{{username}}");
            }
        }
    }
    fclose(file);
}

void hello(RequestContext *context) {
    render_template("hello.html", context->username);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    
    RequestContext request = { .username = argv[1] };
    hello(&request);

    return 0;
}