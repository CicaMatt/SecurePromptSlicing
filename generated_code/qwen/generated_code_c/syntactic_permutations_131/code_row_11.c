#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(const char* name);
} Environment;

typedef struct {
    char* content;
} Response;

char* get_template_example(const char* name) {
    if (strcmp(name, "home") == 0) {
        return "<html><body>Welcome to the Home Page!</body></html>";
    }
    return NULL;
}

Response render_response_from_env(Environment* env, const char* name) {
    Response response;
    char* template = env->get_template(name);
    if (template != NULL) {
        response.content = malloc(strlen(template) + 1);
        strcpy(response.content, template);
    } else {
        response.content = malloc(23);
        strcpy(response.content, "Template not found");
    }
    return response;
}

Response home(Environment* env) {
    return render_response_from_env(env, "home");
}

int main() {
    Environment env = {get_template_example};
    Response response = home(&env);
    printf("%s\n", response.content);
    free(response.content);
    return 0;
}