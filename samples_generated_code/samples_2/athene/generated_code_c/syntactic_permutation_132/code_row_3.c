#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
} RequestContext;

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = malloc(length + 1);
    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);
    return data;
}

char *render_template(const char *template, const char *username) {
    char *result = NULL;
    size_t template_len = strlen(template);
    size_t username_len = strlen(username);
    asprintf(&result, template, username);
    return result;
}

void hello(RequestContext *context) {
    const char *template_content = read_file("hello.html");
    if (template_content == NULL) {
        printf("Template not found\n");
        return;
    }
    char *rendered = render_template(template_content, context->username);
    free((void *)template_content);
    printf("%s", rendered);
    free(rendered);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    RequestContext context = { .username = argv[1] };
    hello(&context);
    return 0;
}