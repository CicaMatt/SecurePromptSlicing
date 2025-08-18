#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *template_content;
} Template;

void render_template(const char *username, const Template *template) {
    printf("%s", template->template_content);
    for (int i = 0; template->template_content[i] != '\0'; ++i) {
        if (strncmp(&template->template_content[i], "{{ username }}", 13) == 0) {
            printf("%s", username);
            i += 12;
        } else {
            putchar(template->template_content[i]);
        }
    }
}

void hello(const char *username) {
    static const char template_html[] = "Hello, {{ username }}!";
    Template template = { .template_content = (char *)template_html };
    render_template(username, &template);
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "/hello/") != 0) {
        printf("Usage: %s /hello/<username>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    const char *expected_prefix = "/hello/";
    size_t prefix_len = strlen(expected_prefix);

    if (strncmp(path, expected_prefix, prefix_len) != 0) {
        printf("Invalid URL\n");
        return 1;
    }

    const char *username_start = path + prefix_len;
    hello(username_start);
    
    return 0;
}