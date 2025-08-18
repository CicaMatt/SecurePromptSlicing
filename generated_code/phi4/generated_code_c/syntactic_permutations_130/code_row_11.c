#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* template;
} Environment;

typedef struct {
    char* content;
} Response;

Response create_response(const char* content) {
    Response response;
    response.content = malloc(strlen(content) + 1);
    if (response.content != NULL) {
        strcpy(response.content, content);
    }
    return response;
}

char* render_template(const char* template, const char* name) {
    size_t buffer_size = strlen(template) + strlen(name) * 2 + 3; // for "Hello %s!"
    char* rendered = malloc(buffer_size);
    if (rendered != NULL) {
        sprintf(rendered, template, name);
    }
    return rendered;
}

Response render_response_from_env(Environment env) {
    Response response;
    char* rendered_content = render_template(env.template, env.name);
    if (rendered_content == NULL) {
        fprintf(stderr, "Failed to render template\n");
        exit(EXIT_FAILURE);
    }

    response = create_response(rendered_content);
    free(rendered_content);

    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World", "Hello %s!"};
    Response response = home(env);

    printf("%s\n", response.content);
    
    free(response.content);
    return 0;
}