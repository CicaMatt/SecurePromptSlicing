#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

typedef struct {
    char content[256];
} Template;

void render_template(Template *template, const char *username) {
    sprintf(template->content, "<html><body>Hello, %s!</body></html>", username);
}

void hello(const char *username) {
    Template template;
    render_template(&template, username);
    printf("%s\n", template.content);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    hello(username);

    return 0;
}